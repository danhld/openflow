#include "OF_Wrapper.h"



OF_Wrapper::OF_Wrapper()
{

}

OF_Wrapper::~OF_Wrapper()
{

}

void OF_Wrapper::setframe(EthernetIIFrame *frame)
{
//    take(frame);
    this->frame = frame;
}
