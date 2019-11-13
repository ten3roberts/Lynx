#pragma once
#include "Events/Event.h"
#include "keycodes.h"
namespace Lynx
{
    class Input
    {
        friend class Application;
    public:
        // Return true if the given key or mouse button was pressed in this frame
        static bool getKeyHit(int keycode);

        // Returns true if the given key or mouse button is held down
        static bool getKeyDown(int keycode);

        //Returns true if the given key or mouse button was released in this frame
        static bool getKeyReleased(int keycode);

    protected:
        static void onEvent(Event& event);
        static void Update();
    private:
        // Includes the state of all keys
        static bool m_keys[KEY_LAST];

        // Includes the state of all keys during the previous frame
        static bool m_prevKeys[KEY_LAST];
        Input();
    };
}