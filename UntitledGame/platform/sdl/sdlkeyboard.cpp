#include "platform/sdl/sdlinput.h"

#include <SDL.h>

SDLKeyboard::SDLKeyboard()
{
    initKeyMappings();

    const Uint8* state = SDL_GetKeyboardState(&mNumKeys);
    mCurrKeys.resize(mNumKeys);
    mPrevKeys.resize(mNumKeys);
    std::copy(state, state + mNumKeys, mCurrKeys.begin());
    std::copy(state, state + mNumKeys, mPrevKeys.begin());
}

// Check if the given key is currently held down
bool SDLKeyboard::isKeyDown(Key key)
{
    SDL_Scancode scancode = keyToSDLScancode(key);
    if (scancode == SDL_SCANCODE_UNKNOWN) return false;
    return mCurrKeys[scancode];
}

// Check if the given key was pressed this frame
bool SDLKeyboard::isKeyPressed(Key key)
{
    SDL_Scancode scancode = keyToSDLScancode(key);
    if (scancode == SDL_SCANCODE_UNKNOWN) return false;
    return !mPrevKeys[scancode] && mCurrKeys[scancode];
}

// Check if the given key was released this frame
bool SDLKeyboard::isKeyReleased(Key key)
{
    SDL_Scancode scancode = keyToSDLScancode(key);
    if (scancode == SDL_SCANCODE_UNKNOWN) return false;
    return mPrevKeys[scancode] && !mCurrKeys[scancode];
}

void SDLKeyboard::update()
{
    // Copy current to previous
    mPrevKeys = mCurrKeys;

    // Get new state from SDL
    const Uint8* state = SDL_GetKeyboardState(NULL);
    std::copy(state, state + mNumKeys, mCurrKeys.begin());
}

SDL_Scancode SDLKeyboard::keyToSDLScancode(Key key) const
{
    auto it = mKeyMapping.find(key);
    return (it != mKeyMapping.end()) ? it->second : SDL_SCANCODE_UNKNOWN;
}

void SDLKeyboard::initKeyMappings()
{
    // Alphanumeric keys
    mKeyMapping[Key::A] = SDL_SCANCODE_A;
    mKeyMapping[Key::B] = SDL_SCANCODE_B;
    mKeyMapping[Key::C] = SDL_SCANCODE_C;
    mKeyMapping[Key::D] = SDL_SCANCODE_D;
    mKeyMapping[Key::E] = SDL_SCANCODE_E;
    mKeyMapping[Key::F] = SDL_SCANCODE_F;
    mKeyMapping[Key::G] = SDL_SCANCODE_G;
    mKeyMapping[Key::H] = SDL_SCANCODE_H;
    mKeyMapping[Key::I] = SDL_SCANCODE_I;
    mKeyMapping[Key::J] = SDL_SCANCODE_J;
    mKeyMapping[Key::K] = SDL_SCANCODE_K;
    mKeyMapping[Key::L] = SDL_SCANCODE_L;
    mKeyMapping[Key::M] = SDL_SCANCODE_M;
    mKeyMapping[Key::N] = SDL_SCANCODE_N;
    mKeyMapping[Key::O] = SDL_SCANCODE_O;
    mKeyMapping[Key::P] = SDL_SCANCODE_P;
    mKeyMapping[Key::Q] = SDL_SCANCODE_Q;
    mKeyMapping[Key::R] = SDL_SCANCODE_R;
    mKeyMapping[Key::S] = SDL_SCANCODE_S;
    mKeyMapping[Key::T] = SDL_SCANCODE_T;
    mKeyMapping[Key::U] = SDL_SCANCODE_U;
    mKeyMapping[Key::V] = SDL_SCANCODE_V;
    mKeyMapping[Key::W] = SDL_SCANCODE_W;
    mKeyMapping[Key::X] = SDL_SCANCODE_X;
    mKeyMapping[Key::Y] = SDL_SCANCODE_Y;
    mKeyMapping[Key::Z] = SDL_SCANCODE_Z;

    // Number keys
    mKeyMapping[Key::Key0] = SDL_SCANCODE_0;
    mKeyMapping[Key::Key1] = SDL_SCANCODE_1;
    mKeyMapping[Key::Key2] = SDL_SCANCODE_2;
    mKeyMapping[Key::Key3] = SDL_SCANCODE_3;
    mKeyMapping[Key::Key4] = SDL_SCANCODE_4;
    mKeyMapping[Key::Key5] = SDL_SCANCODE_5;
    mKeyMapping[Key::Key6] = SDL_SCANCODE_6;
    mKeyMapping[Key::Key7] = SDL_SCANCODE_7;
    mKeyMapping[Key::Key8] = SDL_SCANCODE_8;
    mKeyMapping[Key::Key9] = SDL_SCANCODE_9;

    // Arrow keys
    mKeyMapping[Key::Up] = SDL_SCANCODE_UP;
    mKeyMapping[Key::Down] = SDL_SCANCODE_DOWN;
    mKeyMapping[Key::Left] = SDL_SCANCODE_LEFT;
    mKeyMapping[Key::Right] = SDL_SCANCODE_RIGHT;

    // Function keys
    mKeyMapping[Key::F1] = SDL_SCANCODE_F1;
    mKeyMapping[Key::F2] = SDL_SCANCODE_F2;
    mKeyMapping[Key::F3] = SDL_SCANCODE_F3;
    mKeyMapping[Key::F4] = SDL_SCANCODE_F4;
    mKeyMapping[Key::F5] = SDL_SCANCODE_F5;
    mKeyMapping[Key::F6] = SDL_SCANCODE_F6;
    mKeyMapping[Key::F7] = SDL_SCANCODE_F7;
    mKeyMapping[Key::F8] = SDL_SCANCODE_F8;
    mKeyMapping[Key::F9] = SDL_SCANCODE_F9;
    mKeyMapping[Key::F10] = SDL_SCANCODE_F10;
    mKeyMapping[Key::F11] = SDL_SCANCODE_F11;
    mKeyMapping[Key::F12] = SDL_SCANCODE_F12;

    // Special keys
    mKeyMapping[Key::Space] = SDL_SCANCODE_SPACE;
    mKeyMapping[Key::Enter] = SDL_SCANCODE_RETURN;
    mKeyMapping[Key::Escape] = SDL_SCANCODE_ESCAPE;
    mKeyMapping[Key::Tab] = SDL_SCANCODE_TAB;
    mKeyMapping[Key::Backspace] = SDL_SCANCODE_BACKSPACE;
    mKeyMapping[Key::Delete] = SDL_SCANCODE_DELETE;
    mKeyMapping[Key::LeftShift] = SDL_SCANCODE_LSHIFT;
    mKeyMapping[Key::RightShift] = SDL_SCANCODE_RSHIFT;
    mKeyMapping[Key::LeftCtrl] = SDL_SCANCODE_LCTRL;
    mKeyMapping[Key::RightCtrl] = SDL_SCANCODE_RCTRL;
    mKeyMapping[Key::LeftAlt] = SDL_SCANCODE_LALT;
    mKeyMapping[Key::RightAlt] = SDL_SCANCODE_RALT;
}
