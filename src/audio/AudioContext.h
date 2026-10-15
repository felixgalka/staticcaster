struct AudioContext {

	AudioContext();
	~AudioContext();

	AudioContext(const AudioContext&) = delete;
	AudioContext& operator= (const AudioContext&) = delete;
};