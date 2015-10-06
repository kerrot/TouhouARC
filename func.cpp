#include "func.h"
#include "def.h"

ALuint Buffer[13];
ALuint Source[13];
ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };		// Position of the source sound.
ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };		// Velocity of the source sound.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };		// Position of the Listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };		// Velocity of the Listener.
// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

AUX_RGBImageRec *LoadBMP(const char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

int RGBToRGBA(AUX_RGBImageRec *image)
{
	int width = image->sizeX;
	int height = image->sizeY;
	unsigned char *data;

	data = new unsigned char[width * height * 4];

	for (int i = 0 ; i < width * height ; i++)
	{
		memcpy((void *)&data[i * 4], (void *)&image->data[i * 3] , 3 * sizeof(unsigned char));
			
		if (data[i*4] == 0 & data[i*4+1] == 255 & data[i*4+2] == 0)
			data[i * 4 + 3] = 0;
		else
			data[i * 4 + 3] = 255;
	}

	free(image->data);
	image->data = data;

	return true;
}

bool LoadGLTextures(GLuint *texture, char *filename, bool tga)									// Load Bitmaps And Convert To Textures
{
	bool Status = false;									// Status Indicator

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0]=LoadBMP(filename))
	{
		Status = true;									// Set The Status To TRUE

		if(tga)
			RGBToRGBA(TextureImage[0]);

		glGenTextures(1, texture);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, *texture);
		if(!tga)
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, 4, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}

	return Status;										// Return The Status
}

int LoadTGATextures(GLuint *texture, char *filename)
{
	CTga image;

	image.ReadFile(filename);
	
	glGenTextures(1, texture);					// Create The Texture

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, image.GetSizeX(), image.GetSizeY(), 0, 
				 GL_RGBA, GL_UNSIGNED_BYTE, image.GetPointer());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	if (image.Bpp())
		return true;
	else
		return false;
}

// 判斷是否更新
bool Refresh()
{
	//控叔岕間的相關變數
	static DWORD tick = GetTickCount() , last_tick = GetTickCount() , time_passed;

	// process timer
	last_tick = tick;
	tick = GetTickCount();
	time_passed += (tick - last_tick);
	
	if (time_passed > REFRESH_TIMER)
	{
		time_passed -= REFRESH_TIMER;
		return true;
	}
	else
		return false;
}

ALboolean LoadWave(){
	wavelist("wave/music.wav",		  MUSIC,		0.5f);
	wavelist("wave/player_shot.wav",  PLAYER_SHOT,	0.5f);
	wavelist("wave/bomb.wav",		  BOMB_SOUND,	1.5f);
	wavelist("wave/death.wav",		  DEATH,		1.5f);
	wavelist("wave/get_item.wav",	  GET_ITEM,		1.0f);
	wavelist("wave/enemy_shot1.wav",  ENEMY_SHOT1,	0.3f);
	wavelist("wave/enemy_shot2.wav",  ENEMY_SHOT2,	0.4f);
	wavelist("wave/enemy_shot3.wav",  ENEMY_SHOT3,	0.4f);
	wavelist("wave/enemy_dead.wav",   ENEMY_DEATH,	1.5f);
	wavelist("wave/graze.wav",		  GRAZE,		1.5f);
	wavelist("wave/gameover.wav",	  GAMEOVER,		1.5f);
	wavelist("wave/win.wav",		  WIN,			1.0f);
	wavelist("wave/powerup.wav",	  POWERUP,		1.0f);

	//Set Listener Values
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
	
	return AL_TRUE;
}

void SoundFunc(int choice, int func){
	ALenum sourceState;
	switch(func){
		case PLAY://Play sound 
			alGetSourcei(Source[choice], AL_SOURCE_STATE, &sourceState);
			if(sourceState == AL_PLAYING)
				alSourceStop(Source[choice]); 
			alSourcePlay(Source[choice]);
			break;
		case STOP://Stop sound
			alSourceStop(Source[choice]); 
			break;
		case PAUSE://Pause sound
			alSourcePause(Source[choice]);
			break;
	}
}


ALboolean wavelist(char *title, int num, float volume){
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	// Load wav data into a buffer.
	alGenBuffers(1, &Buffer[num]);
	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alutLoadWAVFile(title, &format, &data, &size, &freq, &loop);//load .wav file
	alBufferData(Buffer[num], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	// Bind the buffer with the source.

	alGenSources(1, &Source[num]);
	if(alGetError() != AL_NO_ERROR)								//error occur
		return AL_FALSE;

	alSourcei (Source[num], AL_BUFFER,   Buffer[num]);
	alSourcef (Source[num], AL_PITCH,    1.0        );
	alSourcef (Source[num], AL_GAIN,     1.0        );
	alSourcefv(Source[num], AL_POSITION, SourcePos  );
	alSourcefv(Source[num], AL_VELOCITY, SourceVel  );
	alSourcei (Source[num], AL_LOOPING,  loop	    );			//loop control
	alSourcef (Source[num], AL_GAIN,	 volume     );			//volume control
	// Do another error check and return.
	return AL_TRUE;
}