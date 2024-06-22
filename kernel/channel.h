enum channelstate {C_UNUSED, C_USED};


struct channel {
    struct spinlock lock;
    int cdescriptor;
    int data; 
    int dataAvailable;   // 1-> There is data, 0-> There is no data
    struct proc *parent; // Creatin parent
    enum channelstate state;
};
