#include <sys/param.h> 
#include <string.h> 
#include <urdf/model.h>
#include <ros/ros.h>



int runExternalProcess(const std::string &executable, const std::string &args)
{
    return system((executable + " " + args).c_str());
}

int main(int argc, char** argv){

	char pwd[MAXPATHLEN];
    getcwd( pwd, MAXPATHLEN );
	runExternalProcess("python `rospack find xacro`/xacro.py", " `rospack find aros_description`/urdf/robot/aros.urdf.xacro > `rospack find aros_description`/test/tmp.urdf" );
	std::string urdf_file = std::string(pwd)+"/src/aros_description/test/tmp.urdf";
	
	ros::init(argc, argv,"aros_urdf_parser");

	urdf::Model model;
	if(!model.initFile(urdf_file)){
		ROS_ERROR("Failed to parse urdf file");
		return -1;
	}

	ROS_INFO("Successfully parsed urdf file");
	return 0;
}
