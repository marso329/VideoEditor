#include "video.h"
Video::Video(QObject* parent):QObject(parent),currentFrame(NULL),open_(false),pFormatCtx(NULL),pVideoCodecCtx(NULL),
pVideoCodec(NULL),pAudioCodecCtx(NULL),pAudioCodec(NULL),codecName(""),videoStreamIndex(-1),audioStreamIndex(-1),
videoFramePerSecond(0),durationUs(0),durationS(0),nb_frames(0),videoBaseTime(0.0),audioBaseTime(0.0),pImgConvertCtx(NULL),
width(0),height(0){

}

Video::Video(std::string filename,QObject* parent) :QObject(parent),currentFrame(NULL),open_(false),pFormatCtx(NULL),pVideoCodecCtx(NULL),
		pVideoCodec(NULL),pAudioCodecCtx(NULL),pAudioCodec(NULL),codecName(""),videoStreamIndex(-1),audioStreamIndex(-1),
		videoFramePerSecond(0),durationUs(0),durationS(0),nb_frames(0),videoBaseTime(0.0),audioBaseTime(0.0),pImgConvertCtx(NULL),
		width(0),height(0){
	open_=false;
	// Open file
	if (avformat_open_input(&pFormatCtx, filename.c_str(), NULL, NULL) != 0) {
		if (pFormatCtx)
		{
			CloseFile();
		}
		return;
	}
	// Get infromation about streams
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		if (pFormatCtx)
		{
			CloseFile();
		}
		return;
	}
	bool res = false;

	if (pFormatCtx)
	{
		videoStreamIndex = -1;

		for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++)
		{
			if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				videoStreamIndex = i;
				pVideoCodecCtx = pFormatCtx->streams[i]->codec;
				pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);

				if (pVideoCodec)
				{
					res     = !(avcodec_open2(pVideoCodecCtx, pVideoCodec, NULL) < 0);
					width   = pVideoCodecCtx->coded_width;
					height  = pVideoCodecCtx->coded_height;
					std::ostringstream temp;
					temp<<pVideoCodec->name;
					codecName=temp.str();
				}

				break;
			}
		}

		if (!res)
		{
			CloseVideo();
		}
		else
		{
			pImgConvertCtx = sws_getContext(pVideoCodecCtx->width, pVideoCodecCtx->height,
				pVideoCodecCtx->pix_fmt,
				pVideoCodecCtx->width, pVideoCodecCtx->height,
				AV_PIX_FMT_RGB555,
				SWS_BICUBIC, NULL, NULL, NULL);
		}
		if(videoStreamIndex != -1)
		{
				videoFramePerSecond = av_q2d(pFormatCtx->streams[videoStreamIndex]->r_frame_rate);
				// Need for convert time to ffmpeg time.
				videoBaseTime       = av_q2d(pFormatCtx->streams[videoStreamIndex]->time_base);
				durationUs = pFormatCtx->duration;
				durationS=durationUs/AV_TIME_BASE;
		}
	}



	open_=true;
	if(videoStreamIndex != -1)
			{
			nb_frames=countFrames();
			}
	_filename=filename;
	_filenameWithoutPath=_filename.substr( _filename.find_last_of("\\/")+1,_filename.size()- _filename.find_last_of("\\/")-1);
	insertFrames();
}

Video::~Video() {

}
std::string Video::getFilenameWithoutPath(){
	return _filenameWithoutPath;
}

bool Video::open() {
	return open_;
}

void Video::CloseVideo()
{
	if (pVideoCodecCtx)
	{
		avcodec_close(pVideoCodecCtx);
		pVideoCodecCtx = NULL;
		pVideoCodec = NULL;
		videoStreamIndex = 0;
	}
}

void Video::CloseAudio()
{
	if (pAudioCodecCtx)
	{
		avcodec_close(pAudioCodecCtx);
		pAudioCodecCtx   = NULL;
		pAudioCodec      = NULL;
		audioStreamIndex = 0;
	}
}
bool Video::CloseFile()
{

	// Close video and audio.
	CloseVideo();
	CloseAudio();

	if (pFormatCtx)
	{
		avformat_close_input(&pFormatCtx);
		pFormatCtx = NULL;
	}

	return true;
}

int64_t Video::countFrames(){
	int64_t counter=0;
	if (videoStreamIndex != -1&&open_)
	{
		AVPacket packet;

		std::cout<<"frame counter"<<std::endl;
		while (av_read_frame(pFormatCtx, &packet) >= 0)
		{
		//	int64_t pts = 0;
		//	pts = (packet.dts != AV_NOPTS_VALUE) ? packet.dts : 0;
			if(packet.stream_index == videoStreamIndex)
			{
				counter++;
			}
			av_free_packet(&packet);

		}
		avformat_seek_file(pFormatCtx, videoStreamIndex, INT64_MIN, 0,
		 INT64_MAX, 0);
		return counter;

	}
	else{
		return counter;
	}
}

void Video::insertFrames(){
//	AVFrame * res = NULL;
     bool first=true;
		if (videoStreamIndex != -1)
		{
			AVFrame *pVideoYuv = av_frame_alloc();
			AVPacket packet;

			if (open_)
			{
				// Read packet.
				while (av_read_frame(pFormatCtx, &packet) >= 0)
				{
		//			int64_t pts = 0;
			//		pts = (packet.dts != AV_NOPTS_VALUE) ? packet.dts : 0;

					if(packet.stream_index == videoStreamIndex)
					{
						// Convert ffmpeg frame timestamp to real frame number.
					//	int64_t numberFrame = (double)((int64_t)pts -
					//		pFormatCtx->streams[videoStreamIndex]->start_time) *
					//		videoBaseTime * videoFramePerSecond;

						// Decode frame
						bool isDecodeComplite = DecodeVideo(&packet, pVideoYuv);
						if (isDecodeComplite)
						{
							std::cout<<"inserted frame"<<std::endl;
							Frame* frame=new Frame(this);
							frame->insertData(pVideoYuv,pImgConvertCtx,width,height);
							frames.push_back(frame);
							if (first){
								currentFrame=frame;
								first=false;
							}

						}

					}
					av_free_packet(&packet);
					packet = AVPacket();
				}

				av_free(pVideoYuv);
			}
		}
}


bool Video::DecodeVideo(const AVPacket *avpkt, AVFrame * pOutFrame)
{
	bool res = false;

	if (pVideoCodecCtx)
	{
		if (avpkt && pOutFrame)
		{
			int got_picture_ptr = 0;
			int videoFrameBytes = avcodec_decode_video2(pVideoCodecCtx, pOutFrame, &got_picture_ptr, avpkt);

//			avcodec_decode_video(pVideoCodecCtx, pOutFrame, &videoFrameBytes, pInBuffer, nInbufferSize);
			res = (videoFrameBytes > 0);
		}
	}

	return res;
}

Frame* Video::getCurrentFrame(){
	return currentFrame;
}
boost::shared_ptr<Frame> Video::getCurrentFramePython(){
	return boost::shared_ptr<Frame> (currentFrame,Frame::do_nothing_deleter);
}
void Video::setCurrentFrame(float value){
	std::size_t frame_number=floor(value*(float)frames.size());
	if (frame_number>frames.size()-1){
		frame_number=frames.size()-1;
	}
	currentFrame=frames.at(frame_number);

}

std::string Video::getProperty(std::string prop){
std::ostringstream temp;

if(prop=="Width"){
	temp<<width;
	return temp.str();
}
if(prop=="Height"){
	temp<<height;
	return temp.str();
}
if(prop=="FPS"){
	temp<<videoFramePerSecond;
	return temp.str();
}
if(prop=="Duration_sec"){
	temp<<durationS;
	return temp.str();
}
if(prop=="CodecName"){
temp<<codecName;
return temp.str();
}
if(prop=="NBFrames"){
temp<<nb_frames;
return temp.str();
}
else{
	return "";
}
}
std::string titles_init[6] = {"Width", "Height","FPS","Duration_sec","CodecName","NBFrames"};
const std::vector<std::string> Video::_properties(titles_init, titles_init+6);
