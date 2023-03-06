module;
#include <dinput.h>
#include <utility>
export module Inputhandler;

/**
 * @brief Keycodes
*/
export enum class Keys
{
	Left = DIK_LEFT,
	Right = DIK_RIGHT,
	Up = DIK_UP,
	Down = DIK_DOWN,
	W = DIK_W,
	A = DIK_A,
	S = DIK_S,
	D = DIK_D
};

/**
 * @brief Class that handles mouse and keyboard input.
 * @details Uses DirectInput internally.
*/
export class InputHandler
{
public:
	/**
	 * @brief Zero initializes the class, for actual initalization see Initialize()
	 * @see Initialize(HINSTANCE, HWND, int, int)
	*/
	constexpr InputHandler() noexcept
		: m_direct_input(nullptr), m_keyboard(nullptr), m_mouse(nullptr), m_keyboard_state(), m_mouse_state(), m_previous_mouse_state(), m_screen_width(0), m_screen_height(0), m_mouse_x(0), m_mouse_y(0)
	{
	}

	/**
	 * @brief Destructor, does nothing, see Shutdown()
	*/
	~InputHandler() noexcept {};

	/**
	 * @brief Move constructor
	*/
	InputHandler(InputHandler&& other) noexcept : InputHandler()
	{
		*this = std::move(other);
	}

	/**
	 * @brief Deleted, DirectInput handles can't be copied.
	*/
	InputHandler(const InputHandler&) = delete;

	/**
	 * @brief Move assignment
	*/
	InputHandler& operator=(InputHandler&& other) noexcept
	{
		if(this == &other) return *this;

		std::swap(m_direct_input, other.m_direct_input);
		std::swap(m_keyboard, other.m_keyboard);
		std::swap(m_mouse, other.m_mouse);
		std::swap(m_keyboard_state, other.m_keyboard_state);
		std::swap(m_mouse_state, other.m_mouse_state);
		std::swap(m_previous_mouse_state, other.m_previous_mouse_state);
		std::swap(m_direct_input, other.m_direct_input);
		std::swap(m_screen_width, other.m_screen_width);
		std::swap(m_screen_height, other.m_screen_height);
		std::swap(m_mouse_x, other.m_mouse_x);

		return *this;
	}

	/**
	 * @brief Deleted, DirectInput handles can't be copied.
	*/
	InputHandler& operator=(const InputHandler&) = delete;

	/**
	 * @brief Initialized the input handler.
	 * @param[in] instance Processor Instance to use.
	 * @param[in] window Window handle to recieve inputs from.
	 * @param[in] screen_width Width of the window.
	 * @param[in] screen_height Height of the window.
	 * @return True if the initialization was successful.
	*/
	bool Initialize(HINSTANCE instance, HWND window, int screen_width, int screen_height) noexcept
	{
		m_screen_width = screen_width;
		m_screen_height = screen_height;
		m_mouse_x = 0;
		m_mouse_y = 0;
		HRESULT result;
		result = DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_direct_input, nullptr);
		if(FAILED(result))
		{
			return false;
		}

		result = m_direct_input->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
		if(FAILED(result))
		{
			return false;
		}

		result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
		if(FAILED(result))
		{
			return false;
		}

		result = m_keyboard->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if(FAILED(result))
		{
			return false;
		}

		result = m_direct_input->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
		if(FAILED(result))
		{
			return false;
		}

		result = m_mouse->SetDataFormat(&c_dfDIMouse);
		if(FAILED(result))
		{
			return false;
		}

		result = m_mouse->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if(FAILED(result))
		{
			return false;
		}

		// These not being aquired is a valid result and happens if the window starts minimized.
		result = m_keyboard->Acquire();
		result = m_mouse->Acquire();

		return true;
	}

	/**
	 * @brief Releases all input handles used by the class.
	*/
	void Shutdown() noexcept
	{
		if(m_mouse)
		{
			m_mouse->Unacquire();
			m_mouse->Release();
		}

		if(m_keyboard)
		{
			m_keyboard->Unacquire();
			m_keyboard->Release();
		}

		if(m_direct_input)
		{
			m_direct_input->Release();
		}

		return;
	}

	/**
	 * @brief Processes all events that has taken place since the last call.
	 * @return True if the processing worked, False if any error occured.
	*/
	bool Update() noexcept
	{
		bool result;

		result = ReadKeyboard();
		if(!result)
		{
			return false;
		}

		result = ReadMouse();
		if(!result)
		{
			return false;
		}

		ProcessInput();

		return true;
	}

	/**
	 * @brief Gets the current X and Y location of the mouse cursor.
	 * @param[out] mouse_x Will be set to the X coordinate of the mouse.
	 * @param[out] mouse_y Will be set to the Y coordinate of the mouse.
	*/
	void GetMouseLocation(int& mouse_x, int& mouse_y) const noexcept
	{
		mouse_x = m_mouse_x;
		mouse_y = m_mouse_y;
	}

	/**
	 * @brief Check if the given key if currently pressed.
	 * @param[in] key Keycode of the key to check @see Keys
	 * @return True if the key is currently held down.
	*/
	bool IsKeyPressed(Keys key) const noexcept
	{
		return m_keyboard_state[(int)key] & 0x80;
	}

	/**
	 * @brief Gets the mouse X delta since last Update()
	 * @return Pixels moved in X since last Update()
	*/
	long GetMouseDeltaX() const noexcept
	{
		return m_mouse_state.lX;
	}

	/**
	 * @brief Gets the mouse Y delta since last Update()
	 * @return Pixels moved in Y since last Update()
	*/
	long GetMouseDeltaY() const noexcept
	{
		return m_mouse_state.lY;
	}

private:
	IDirectInput8* m_direct_input;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;
	unsigned char m_keyboard_state[256];
	DIMOUSESTATE m_mouse_state, m_previous_mouse_state;
	int m_screen_width, m_screen_height;
	int m_mouse_x, m_mouse_y;

	bool ReadKeyboard() noexcept
	{
		HRESULT result;

		result = m_keyboard->GetDeviceState(sizeof(m_keyboard_state), (LPVOID)&m_keyboard_state);
		if(FAILED(result))
		{
			if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				m_keyboard->Acquire();
			}
			else
			{
				return false;
			}
		}

		return true;
	}

	bool ReadMouse() noexcept
	{
		HRESULT result;
		m_previous_mouse_state = m_mouse_state;
		result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouse_state);
		if(FAILED(result))
		{
			if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				m_mouse->Acquire();
			}
			else
			{
				return false;
			}
		}

		return true;
	}

	void ProcessInput() noexcept
	{
		m_mouse_x += m_mouse_state.lX;
		m_mouse_y += m_mouse_state.lY;
	}
};