Step 1.
Before run compile those projects MessageInterface, NetCode

copy: libMessageInterface.so from MessageInterface project
copy: libNetCode.so from NetCode/Output project

and paste into this folder (UdpClient)

Step 2.
copy: MessageInterface, NetCod projects
and paste into folder
UdpClient/InternalLib

Step 3.
before run program do in terminal:

export LD_LIBRARY_PATH=lib/:$LD_LIBRARY_PATH
then
./main
