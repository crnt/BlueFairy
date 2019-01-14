#ifndef __ARC__KEYBOARD__
#define __ARC__KEYBOARD__
#include "EdgeDetector.h"

namespace arc {

    class KeyEvent {
    public:
        size_t key;
        Edge edge;
        unsigned int holdTicks;
        unsigned long lastChange;

        KeyEvent(size_t key, Edge edge, unsigned int holdTicks, unsigned long lastChange) {
            this->key = key;
            this->edge = edge;
            this->holdTicks = holdTicks;
            this->lastChange = lastChange;
        }

        unsigned int holdTime() const {
            return millis() - this->lastChange;
        }

    };

    typedef void (*key_action_t)(const KeyEvent&);
    key_action_t noop = [](const KeyEvent& event){};


    template<size_t SIZE>
    class Keyboard {
    public:
        Keyboard(const byte* const pins);
        void tick();
        unsigned long lastTick;
        unsigned long lastChange[SIZE];
        unsigned int holdTicks[SIZE];
        key_action_t onKeyDown[SIZE];
        key_action_t onKeyUp[SIZE];
        void edgeTrigger(const Edge* const edges);
        void operator()(const Edge* const edges);
    protected:
        EdgeDetector<SIZE, Keyboard&> edgeDetector;
    };

    template<size_t SIZE>
    Keyboard<SIZE>::Keyboard(const byte* const pins): edgeDetector(pins,*this){
        this->lastTick = millis();
        for(size_t i =0;i<SIZE;++i){
            this->onKeyDown[i] = noop;
            this->onKeyUp[i] = noop;
            this->holdTicks[i] = -1;
            this->lastChange[i] = 0;
        }
    }

    template<size_t SIZE>
    void Keyboard<SIZE>::operator()(const Edge* const edges){
        this->edgeTrigger(edges);
    }

    template<size_t SIZE>
    void Keyboard<SIZE>::edgeTrigger(const Edge* const edges){
        const unsigned long now = millis();
        for(size_t i =0;i<SIZE;i+=1){
            const unsigned int holdTicks = this->holdTicks[i];
            const unsigned long lastChange = this->lastChange[i];
            KeyEvent event(i, edges[i], holdTicks, lastChange);
            switch(edges[i]){
                case Edge::Negedge:
                    this->holdTicks[i] = -1;
                    this->lastChange[i] = now;
                    this->onKeyDown[i](event);
                    break;
                case Edge::Posedge:
                    this->holdTicks[i] = -1;
                    this->onKeyUp[i](event);
                    this->lastChange[i] = now;
                    break;
                case Edge::None:
                default:
                    break;
            }
        }
    }

    template<size_t SIZE>
    void Keyboard<SIZE>::tick() {
        for(size_t i = 0; i < SIZE; ++i){
            this->holdTicks[i] += 1;
        }
        this->edgeDetector.tick();
    }

}

#endif