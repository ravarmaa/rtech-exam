# rtech-exam

My first idea was to create a server-client pair, where you can send some input for example 1 for forwards and 0 for backwards. Depending on that
input, the server returns either positive or negative geometry_msgs/Twist x value. Positive is for forwards and negative for backwards.

Then I thought it is simpler to just put a publisher inside the server node. The client sends some value and the server then replies with "OK" or "ack" and then proceeds to continuously publish some value so that Husy would go in the right direction.

Getting the server-client nodes working took the most time. Some stupid things took lots of time, for example I forgot to start the server node and wondered why the addition from server-client tutorial did not work. 

The whole code was actually based on that tutorial. At first I tried writing the full code right away (in command_client and command_server files), but as this failed to build, I started over by making small changes to the working code. 

Finally I was able to get the client-server nodes working so that I send some two numbers and the sum was returned. The first number, however is published to /vel_cmd topic. I did not have the time to test if publishing once makes the husky move continuously or not. 

Okay It works now, having positive integer as the first number makes the robot move in one direction and negative value in the other direction.

The movement is not continuous, though. This should be fixable with ros time and periodic publishing.