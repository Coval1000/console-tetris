#pragma once

#include <stdbool.h>
#include <windows.h>

#define KEY_INPUT (0xE0)
#define KEY_STATE(key_code) (GetAsyncKeyState(key_code) & 0x8000)

typedef struct Key
{
    bool isDown;
    bool isFalling;
    bool isRising;
    char code;
} Key_t;

void _Process_Key(Key_t *self);
void key_init(Key_t *self, char code);

typedef struct NumKeys
{
    Key_t num0;
    Key_t num1;
    Key_t num2;
    Key_t num3;
    Key_t num4;
    Key_t num5;
    Key_t num6;
    Key_t num7;
    Key_t num8;
    Key_t num9;

    void(*Process_Input)(struct NumKeys *self);
    void(*Default)(struct NumKeys *self);
}NumKeys;

void _NumKeys_Default(struct NumKeys *self);
void _NumKeys_ProcessInput(struct NumKeys *self);
void _NumKeys_Initialize(struct NumKeys *self);

typedef struct DirectionKeys
{
    Key_t up;
    Key_t down;
    Key_t left;
    Key_t right;
    void(*Process_Input)(struct DirectionKeys *self);
    void(*Default)(struct DirectionKeys *self);
}DirectionKeys;

void _DirectionKeys_Default(struct DirectionKeys *self);
void _DirectionKeys_ProcessInput(struct DirectionKeys *self);
void _DirectionKeys_Initialize(struct DirectionKeys *self);

typedef struct UtilityKeys
{
    Key_t esc;
    Key_t enter;
    Key_t backspace;
    void(*Process_Input)(struct UtilityKeys *self);
    void(*Default)(struct UtilityKeys *self);
}UtilityKeys;

void _UtilityKeys_Default(struct UtilityKeys *self);
void _UtilityKeys_ProcessInput(struct UtilityKeys *self);
void _UtilityKeys_Initialize(struct UtilityKeys *self);
