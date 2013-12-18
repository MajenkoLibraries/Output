/*
 * Copyright (c) 2013, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <Output.h>

Output::Output(uint8_t p, uint8_t def) {
    currentState = def;
    pin = p;
    _cbOnHigh = NULL;
    _cbOnLow = NULL;
    _cbOnChange = NULL;
}

void Output::begin() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, currentState);
}

void Output::high() {
    if (currentState == HIGH) return;
    currentState = HIGH;
    digitalWrite(pin, currentState);
    callback();
}

void Output::low() {
    if (currentState == LOW) return;
    currentState = LOW;
    digitalWrite(pin, currentState);
    callback();
}

void Output::toggle() {
    currentState = !currentState;
    digitalWrite(pin, currentState);
    callback();
}

uint8_t Output::getState() {
    return currentState;
}

void Output::onHigh(void (*func)(uint8_t)) {
    _cbOnHigh = func;
}

void Output::onLow(void (*func)(uint8_t)) {
    _cbOnLow = func;
}

void Output::onChange(void (*func)(uint8_t)) {
    _cbOnChange = func;
}

void Output::callback() {
    if (_cbOnHigh && currentState) {
        _cbOnHigh(currentState);
    }
    if (_cbOnLow && !currentState) {
        _cbOnLow(currentState);
    }
    if (_cbOnChange) {
        _cbOnChange(currentState);
    }
}
