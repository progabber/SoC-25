These are modified "atkbd.c" files. 
The modifications for both atkbd\_1.c and atkbd\_2.c have been done in the "atkbd\_receive\_bytes" function. <br>

For the third part, there is an external LKM `toggle\_good.c` loading which switches on keylogging and removing stops keylogging. 
The modifications to atkbd\_3.c are not limited to the atkbd\_receive\_bytes function but helper functions have been definnnnnned to set up a workqueue.
This was necessary because the keypresses are handled in interrupt context and the kernel cannot read/write files then. 
So writing is deferred to a later suitable time.

(The last part saw use of LLMs for creating workqueues)
