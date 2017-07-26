#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <std_msgs/Bool.h>
#include <functional>
#include <ros/ros.h>




class Stereo {
    public:
        Stereo();
        
        image_transport::Subscriber image_sub_left;
    
        image_transport::Subscriber image_sub_right;

        std::vector<ImageCallback> image_callbacks_left;

        std::vector<ImageCallback> image_callbacks_;

        ros::NodeHandle nh_;
        image_transport::ImageTransport it_;
        
        void OnImage(ImageCallback callback);

        void onImage(const sensor_msgs::ImageConstPtr& msg);

}


Stereo::Stereo() :it_( nh_ ){
        image_sub_left  = it_.subscribe( "left/image_raw" , 1, &Stereo::onImage, this);
        image_sub_right = it_.subscribe( "right/image_raw", 1, &Stereo::onImage, this);

}


void Stereo::onImage(const sensor_msgs::ImageConstPtr& msg) {
        for(int i = 0; i < image_callbacks_.size(); i++) {
                    image_callbacks_[i](cv_bridge::toCvShare(msg, "rgb8"));
                        }
}

void Stereo::OnImage(ImageCallback callback) {
        image_callbacks_.push_back(callback);
}
     
