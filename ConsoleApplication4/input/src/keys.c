#include "../keys.h"

void _Process_Key(Key_t *self)
{
    bool result = GetAsyncKeyState(self->code) & 0x8000;
    if (result)
    {		
        if (self->isDown) 
        {
            self->isRising = false;
        }
        else
        {
            self->isRising = true;
        }
        self->isFalling = false;
        self->isDown = true;
    }
    else
    {
        if (self->isDown) 
        {
            self->isFalling = true;
        }
        else 
        {
            self->isFalling = false;
        }
        self->isRising = false;
        self->isDown = false;
    }
    return;
}

void key_init(Key_t *self, char code)
{
    self->code = code;
    self->isDown = false;
    self->isFalling = false;
    self->isRising = false;
    return;
}

void _NumKeys_Default(struct NumKeys *self)
{
    key_init(&self->num0, '0');
    key_init(&self->num1, '1');
    key_init(&self->num2, '2');
    key_init(&self->num3, '3');
    key_init(&self->num4, '4');
    key_init(&self->num5, '5');
    key_init(&self->num6, '6');
    key_init(&self->num7, '7');
    key_init(&self->num8, '8');
    key_init(&self->num9, '9');
    return;
}

void _NumKeys_ProcessInput(struct NumKeys *self)
{
    _Process_Key(&self->num0);
    _Process_Key(&self->num1);
    _Process_Key(&self->num2);
    _Process_Key(&self->num3);
    _Process_Key(&self->num4);
    _Process_Key(&self->num5);
    _Process_Key(&self->num6);
    _Process_Key(&self->num7);
    _Process_Key(&self->num8);
    _Process_Key(&self->num9);
    return;
}

void _NumKeys_Initialize(struct NumKeys *self)
{
    self->Process_Input = &_NumKeys_ProcessInput;
    self->Default = &_NumKeys_Default;
    _NumKeys_Default(self);
    return;
}

void _DirectionKeys_Default(struct DirectionKeys *self)
{
    key_init(&self->up, VK_UP);
    key_init(&self->down, VK_DOWN);
    key_init(&self->left, VK_LEFT);
    key_init(&self->right, VK_RIGHT);
    return;
}

void _DirectionKeys_ProcessInput(struct DirectionKeys *self)
{
    _Process_Key(&self->down);
    _Process_Key(&self->up);
    _Process_Key(&self->left);
    _Process_Key(&self->right);
    return;
}

void _DirectionKeys_Initialize(struct DirectionKeys *self)
{
    self->Process_Input = &_DirectionKeys_ProcessInput;
    self->Default = &_DirectionKeys_Default;
    _DirectionKeys_Default(self);
    return;
}

void _UtilityKeys_Default(struct UtilityKeys *self)
{
    key_init(&self->esc, VK_ESCAPE);
    key_init(&self->enter, VK_RETURN);
    key_init(&self->backspace, VK_BACK);
    return;
}

void _UtilityKeys_ProcessInput(struct UtilityKeys *self)
{
    _Process_Key(&self->esc);
    _Process_Key(&self->enter);
    _Process_Key(&self->backspace);
    return;
}

void _UtilityKeys_Initialize(struct UtilityKeys *self)
{
    self->Process_Input = &_UtilityKeys_ProcessInput;
    self->Default = &_UtilityKeys_Default;
    _UtilityKeys_Default(self);
    return;
}