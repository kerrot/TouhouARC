// #include <windows.h>		// Header File For Windows
// #include <stdio.h>			// Header File For Standard Input/Output
// #include <string>
// #include <gl/glut.h>
// #include <time.h>
// #include "def.h"
// #include "obj.h"
// #include "func.h"
// 
// 
// 
// 
// HDC			hDC=NULL;		// Private GDI Device Context
// HGLRC		hRC=NULL;		// Permanent Rendering Context
// HWND		hWnd=NULL;		// Holds Our Window Handle
// HINSTANCE	hInstance;		// Holds The Instance Of The Application
// 
// //ｰﾊｵeｧsﾀWｲv
// #define ID_TIMER 456
// #define TIMER_TIME 33	//TIMERｮﾉｶ｡
// 
// bool	keys[256];			// Array Used For The Keyboard Routine
// bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
// bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
// 
// BG bg;
// Game game;
// 
// LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
// 
// int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
// {
// 	if(LoadWave() == AL_FALSE)						//load wave
// 	{
// 	    MessageBox(NULL,"LOADWAVE FAIL","ERROR",MB_OK | MB_ICONINFORMATION);
// 		exit(0);
// 	}
// 	bg.init();		//ｪ・l､ﾆ
// 	game.init();
// 
// 	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
// 	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
// 	
// 	glEnable(GL_BLEND);									//Enable ｳzｩ・
//	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
// 
// 	glClearDepth(1.0f);									// Depth Buffer Setup
// 	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
// 	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
// 	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
// 	return TRUE;										// Initialization Went OK
// }
// 
// GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
// {
// 	if (height==0)										// Prevent A Divide By Zero By
// 	{
// 		height=1;										// Making Height Equal One
// 	}
// 
// 	glViewport(0,0,width,height);						// Reset The Current Viewport
// 
// 	
// 	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
// 	glLoadIdentity();									// Reset The Projection Matrix
// 	
// 	//ｳ]ｩw2Dｧ・vｯxｰ}
// 	gluOrtho2D(0, (GLfloat)WINDOWX, (GLfloat)WINDOWY, 0);
// 	
// 	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
// 	glLoadIdentity();									// Reset The Modelview Matrix
// }
// 
// int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
// {
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//ｵeｹﾏ
// 
//  	bg.display();
//  	game.display();
// 
// 	return TRUE;										// Keep Going
// }
// 
// void keyboard(){//ﾁ菴Lｾﾞｧ@
// 
// 	if(keys[VK_LEFT])
// 		(keys[VK_SHIFT])? game.act(SLOW_LEFT) : game.act(MOVE_LEFT);
// 	if(keys[VK_RIGHT])
// 		(keys[VK_SHIFT])? game.act(SLOW_RIGHT) : game.act(MOVE_RIGHT);
// 	if(keys[VK_UP])
// 		(keys[VK_SHIFT])? game.act(SLOW_UP) : game.act(MOVE_UP);
// 	if(keys[VK_DOWN])
// 		(keys[VK_SHIFT])? game.act(SLOW_DOWN) : game.act(MOVE_DOWN);
// 	if(keys[0x58])
// 		game.act(BOMB);
// 	if(keys[0x5A])
// 		game.act(FIRE);
// 	if(keys[VK_F2])
// 		game.act(POWERUP);
// 	if(keys[VK_RETURN])
// 		game.act(ENTER);
// }
// 
// VOID CALLBACK timer( 
//     HWND hwnd,        // handle to window for timer messages 
//     UINT message,     // WM_TIMER message 
//     UINT idTimer,     // timer identifier 
//     DWORD dwTime)     // current system time 
// { 
// 	keyboard();
// 	game.goon();
//     DrawGLScene();
// } 
// 
// 
// 
// GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
// {
// 	if (fullscreen)										// Are We In Fullscreen Mode?
// 	{
// 		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
// 		ShowCursor(TRUE);								// Show Mouse Pointer
// 	}
// 
// 	if (hRC)											// Do We Have A Rendering Context?
// 	{
// 		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
// 		{
// 			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
// 		}
// 
// 		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
// 		{
// 			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
// 		}
// 		hRC=NULL;										// Set RC To NULL
// 	}
// 
// 	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
// 	{
// 		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
// 		hDC=NULL;										// Set DC To NULL
// 	}
// 
// 	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
// 	{
// 		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
// 		hWnd=NULL;										// Set hWnd To NULL
// 	}
// 
// 	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
// 	{
// 		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
// 		hInstance=NULL;									// Set hInstance To NULL
// 	}
// }
// 
// /*	This Code Creates Our OpenGL Window.  Parameters Are:					*
//  *	title			- Title To Appear At The Top Of The Window				*
//  *	width			- Width Of The GL Window Or Fullscreen Mode				*
//  *	height			- Height Of The GL Window Or Fullscreen Mode			*
//  *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
//  *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
//  
// BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
// {
// 	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
// 	WNDCLASS	wc;						// Windows Class Structure
// 	DWORD		dwExStyle;				// Window Extended Style
// 	DWORD		dwStyle;				// Window Style
// 	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
// 	WindowRect.left=(long)0;			// Set Left Value To 0
// 	WindowRect.right=(long)width;		// Set Right Value To Requested Width
// 	WindowRect.top=(long)0;				// Set Top Value To 0
// 	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height
// 
// 	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag
// 
// 	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
// 	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
// 	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
// 	wc.cbClsExtra		= 0;									// No Extra Window Data
// 	wc.cbWndExtra		= 0;									// No Extra Window Data
// 	wc.hInstance		= hInstance;							// Set The Instance
// 	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
// 	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
// 	wc.hbrBackground	= NULL;									// No Background Required For GL
// 	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
// 	wc.lpszClassName	= "OpenGL";								// Set The Class Name
// 
// 	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
// 	{
// 		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
// 		return FALSE;											// Return FALSE
// 	}
// 	
// 	if (fullscreen)												// Attempt Fullscreen Mode?
// 	{
// 		DEVMODE dmScreenSettings;								// Device Mode
// 		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
// 		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
// 		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
// 		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
// 		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
// 		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
// 
// 		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
// 		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
// 		{
// 			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
// 			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
// 			{
// 				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
// 			}
// 			else
// 			{
// 				// Pop Up A Message Box Letting User Know The Program Is Closing.
// 				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
// 				return FALSE;									// Return FALSE
// 			}
// 		}
// 	}
// 
// 	if (fullscreen)												// Are We Still In Fullscreen Mode?
// 	{
// 		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
// 		dwStyle=WS_POPUP;										// Windows Style
// 		ShowCursor(FALSE);										// Hide Mouse Pointer
// 	}
// 	else
// 	{
// 		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
// 		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
// 	}
// 
// 	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size
// 
// 	// Create The Window
// 	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
// 								"OpenGL",							// Class Name
// 								title,								// Window Title
// 								dwStyle |							// Defined Window Style
// 								WS_CLIPSIBLINGS |					// Required Window Style
// 								WS_CLIPCHILDREN,					// Required Window Style
// 								0, 0,								// Window Position
// 								WindowRect.right-WindowRect.left,	// Calculate Window Width
// 								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
// 								NULL,								// No Parent Window
// 								NULL,								// No Menu
// 								hInstance,							// Instance
// 								NULL)))								// Dont Pass Anything To WM_CREATE
// 	{
// 		KillGLWindow();								// Reset The Display
// 		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
// 		return FALSE;								// Return FALSE
// 	}
// 
// 	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
// 	{
// 		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
// 		1,											// Version Number
// 		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
// 		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
// 		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
// 		PFD_TYPE_RGBA,								// Request An RGBA Format
// 		bits,										// Select Our Color Depth
// 		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
// 		0,											// No Alpha Buffer
// 		0,											// Shift Bit Ignored
// 		0,											// No Accumulation Buffer
// 		0, 0, 0, 0,									// Accumulation Bits Ignored
// 		16,											// 16Bit Z-Buffer (Depth Buffer)  
// 		0,											// No Stencil Buffer
// 		0,											// No Auxiliary Buffer
// 		PFD_MAIN_PLANE,								// Main Drawing Layer
// 		0,											// Reserved
// 		0, 0, 0										// Layer Masks Ignored
// 	};
// 	
// 	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
// 	{
// 		KillGLWindow();								// Reset The Display
// 		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
// 		return FALSE;								// Return FALSE
// 	}
// 
// 	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
// 	{
// 		KillGLWindow();								// Reset The Display
// 		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
// 		return FALSE;								// Return FALSE
// 	}
// 
// 	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
// 	{
// 		KillGLWindow();								// Reset The Display
// 		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
// 		return FALSE;								// Return FALSE
// 	}
// 
// 	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
// 	{
// 		KillGLWindow();								// Reset The Display
// 		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
// 		return FALSE;								// Return FALSE
// 	}
// 
// 	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
// 	{
// 		KillGLWindow();								// Reset The Display
// 		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
// 		return FALSE;								// Return FALSE
// 	}
// 
// 	ShowWindow(hWnd,SW_SHOW);						// Show The Window
// 	SetForegroundWindow(hWnd);						// Slightly Higher Priority
// 	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
// 	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen
// 
// 	if (!InitGL())									// Initialize Our Newly Created GL Window
// 	{
// 		KillGLWindow();								// Reset The Display
// 		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
// 		return FALSE;								// Return FALSE
// 	}
// 
// 	return TRUE;									// Success
// }
// 
// LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
// 							UINT	uMsg,			// Message For This Window
// 							WPARAM	wParam,			// Additional Message Information
// 							LPARAM	lParam)			// Additional Message Information
// {
// 	switch (uMsg)									// Check For Windows Messages
// 	{
// 		case WM_ACTIVATE:							// Watch For Window Activate Message
// 		{
// 			if (!HIWORD(wParam))					// Check Minimization State
// 			{
// 				active=TRUE;						// Program Is Active
// 			}
// 			else
// 			{
// 				active=FALSE;						// Program Is No Longer Active
// 			}
// 
// 			return 0;								// Return To The Message Loop
// 		}
// 
// 		case WM_SYSCOMMAND:							// Intercept System Commands
// 		{
// 			switch (wParam)							// Check System Calls
// 			{
// 				case SC_SCREENSAVE:					// Screensaver Trying To Start?
// 				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
// 				return 0;							// Prevent From Happening
// 			}
// 			break;									// Exit
// 		}
// 
// 		case WM_CLOSE:								// Did We Receive A Close Message?
// 		{
// 			PostQuitMessage(0);						// Send A Quit Message
// 			return 0;								// Jump Back
// 		}
// 
// 		case WM_KEYDOWN:							// Is A Key Being Held Down?
// 		{
// 			keys[wParam] = TRUE;					// If So, Mark It As TRUE
// 			return 0;								// Jump Back
// 		}
// 
// 		case WM_KEYUP:								// Has A Key Been Released?
// 		{
// 			keys[wParam] = FALSE;					// If So, Mark It As FALSE
// 			return 0;								// Jump Back
// 		}
// 
// 		case WM_SIZE:								// Resize The OpenGL Window
// 		{
// 			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
// 			return 0;								// Jump Back
// 		}
// 		case WM_TIMER:								// Resize The OpenGL Window
// 		{
// 			timer(hWnd,uMsg,ID_TIMER, TIMER_TIME);  // LoWord=Width, HiWord=Height
// 			return 0;								// Jump Back
// 		}
// 	}
// 
// 	// Pass All Unhandled Messages To DefWindowProc
// 	return DefWindowProc(hWnd,uMsg,wParam,lParam);
// }
// 
// int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
// 					HINSTANCE	hPrevInstance,		// Previous Instance
// 					LPSTR		lpCmdLine,			// Command Line Parameters
// 					int			nCmdShow)			// Window Show State
// {
// 	MSG		msg;									// Windows Message Structure
// 	alutInit(0, NULL);								//openalｪ・l
// 	BOOL	done=FALSE;								// Bool Variable To Exit Loop
// 	srand( time(NULL) );							//ｶﾃｼﾆ
// 
// 	// Ask The User Which Screen Mode They Prefer
// 	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
// 	{
// 		fullscreen=FALSE;							// Windowed Mode
// 	}
// 
// 	// Create Our OpenGL Window
// 	if (!CreateGLWindow("3D_HW3", WINDOWX, WINDOWY,16, fullscreen))
// 	{
// 		return 0;									// Quit If Window Was Not Created
// 	}
//     
// 	SetTimer(hWnd, ID_TIMER, TIMER_TIME, (TIMERPROC) timer);
// 
// 	while(!done)									// Loop That Runs While done=FALSE
// 	{
// 		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
// 		{
// 			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
// 			{
// 				done=TRUE;							// If So done=TRUE
// 			}
// 			else									// If Not, Deal With Window Messages
// 			{
// 				TranslateMessage(&msg);				// Translate The Message
// 				DispatchMessage(&msg);				// Dispatch The Message
// 			}
// 		}
// 		else										// If There Are No Messages
// 		{
// 			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
// 			if (!active || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
// 			{
// 				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
// 			}
// 			else									// Not Time To Quit, Update Screen
// 			{
// 				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
// 			}
// 
// 			if (keys[VK_F1])						// Is F1 Being Pressed?
// 			{
// 				keys[VK_F1]=FALSE;					// If So Make Key FALSE
// 				KillTimer(hWnd, ID_TIMER);
// 				KillGLWindow();						// Kill Our Current Window
// 				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
// 				// Recreate Our OpenGL Window
// 				
// 				if (!CreateGLWindow("3D_HW3", WINDOWX, WINDOWY,16,fullscreen))
// 				{
// 					return 0;						// Quit If Window Was Not Created
// 				}
// 				SetTimer(hWnd, ID_TIMER, TIMER_TIME, (TIMERPROC) timer);
// 			}
// 		}
// 	}
//     
//     KillTimer(hWnd, ID_TIMER); 
// 
// 	//Shutdown
// 	KillGLWindow();									// Kill The Window
// 	return (msg.wParam);							// Exit The Program
// }
