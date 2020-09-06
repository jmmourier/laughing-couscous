#ifndef SIMPLE_WEBSOCKET_SERVER_REGISTRY_ELEMENT_H
#define SIMPLE_WEBSOCKET_SERVER_REGISTRY_ELEMENT_H


class registry_element {
public:
    registry_element();
    int getVal();
    bool isEmpty();
    void setVal(int value);

private:
    int val;
    bool empty;
};


#endif //SIMPLE_WEBSOCKET_SERVER_REGISTRY_ELEMENT_H
