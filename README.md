PowerMonitor
==============
PowerMonitor is a Windows application written in C++11 that switches between low, balanced and high power plan depending on the processes that are running. The idea is to use the most appropriate power plan for the activity. The power saver plan should be used when running processes that don't require much computing power (e.g. watching a video), while the high performance plan should be used when running processes that require a lot of computing power (e.g. games), and in other cases fall back to the default scheme (balanced) which scales for most activity.

Why not just one power plan?
==============
If you have the ideal power plan for any kind of activity, there might not be any reason for you switch between different power plans. In my case, I don't like to hear my CPU fan when I watch videos, but I don't mind if the CPU fan is loud when playing games.

Configuration
==============
The process list and power plan names can be configured in config.hpp.