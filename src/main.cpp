#include "videos.h"
#include <iostream>

int main(){

	Videos* videoContainer=new Videos();
	 if(videoContainer->addVideo("../test/bird.avi")){
		 std::cout<<"success"<<std::endl;

	 }
	 else{
		 std::cout<<"fail"<<std::endl;
	 }

}
