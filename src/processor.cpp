#include "processor.h"
#include "linux_parser.h"
// TODO: Return the aggregate CPU utilization
Processor::Processor(){
	jAll_ = LinuxParser::Jiffies();
	jIdle_ = LinuxParser::IdleJiffies();
}
float Processor::Utilization() { 
	float jAllPrev = jAll_;
	float jIdlePrev = jIdle_;
	jAll_ = LinuxParser::Jiffies();
	jIdle_ = LinuxParser::IdleJiffies();

	float utilization = ((jAll_ - jAllPrev) - (jIdle_ - jIdlePrev)) / (jAll_ - jAllPrev);
	return (utilization > 0.0 ) ? utilization : 0.0;
}