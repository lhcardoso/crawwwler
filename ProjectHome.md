This project is still in its absolute infancy.

craWWWler will be a large scale web crawler written in C++ (no MFC). It currently has a very basic plugin architecture controlled by a purposely thin manager.  The manager, however, is designed to be more like an ignition switch, occasional pump, and emergency shutdown.

The manager is responsible for allowing one or mores plugins to subscribe to the output of other plugins.  In this way, the plugins do not have to pass large amounts of data to other plugins via the manager class. Data is only passed on to interested parties.

**WARNING** DO NOT let this loose on the web.  Test it on a site you've downloaded onto your local machine and don't let it get anywhere near the WWW yet! It is NOT STABLE! We don't want to go around crashing sites because we don't yet know what we're doing!  There are a lot of laws and caveats out there we need to be very aware of.  The primary purpose of this software is availability of information, so lets keep it both legal and helpful.

p.s. its an eclipse managed build project because I'm new to coding in Linux and don't know any better.  Anyone have guidance on this?