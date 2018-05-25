///////////////////////////////////////////////////////////////////////////////
///
/// Author: Andrea Ellinger
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef AudioIOInterface_H
#define AudioIOInterface_H

namespace Audio
{
  using namespace Zero;

  inline static void LogAudioIoError(Zero::StringParam message, Zero::String* savedMessage = nullptr)
  {
    ZPrint(Zero::String::Format(message.c_str(), "\n").c_str());
    if (savedMessage)
      *savedMessage = message;
  }

  class StreamInfo
  {
  public:
    StreamInfo() : 
      mStatus(StreamStatus::Uninitialized),
      mChannels(0),
      mSampleRate(0)
    {}

    StreamStatus::Enum mStatus;
    Zero::String mErrorMessage;
    unsigned mChannels;
    unsigned mSampleRate;
  };

  void IOCallback(float* outputBuffer, float* inputBuffer, unsigned framesPerBuffer, void* data);

  //----------------------------------------------------------------------------- Audio Input Output

  class AudioIOInterface
  {
  public:
    AudioIOInterface();
    ~AudioIOInterface();

    // Initializes the audio API and the input & output streams
    bool Initialize();
    // Shuts down the audio API. Streams should be already stopped.
    void ShutDown();
    // Starts the output and/or input streams, depending on parameters
    bool StartStreams(bool startOutput, bool startInput);
    // Stops the output and/or input streams, depending on parameters
    bool StopStreams(bool stopOutput, bool stopInput);
    // Returns the current status of the specified audio stream
    StreamStatus::Enum GetStreamStatus(StreamTypes::Enum whichStream);
    // Returns the last error message associated with the specified audio stream
    const Zero::String& GetStreamErrorMessage(StreamTypes::Enum whichStream);
    // Returns the last error message associated with the audio API
    const Zero::String& GetSystemErrorMessage();
    // Returns the number of channels in the specified audio stream
    unsigned GetStreamChannels(StreamTypes::Enum whichStream);
    // Returns the sample rate of the specified audio stream
    unsigned GetStreamSampleRate(StreamTypes::Enum whichStream);
    // Waits until another mix is needed, using semaphore counter
    void WaitUntilOutputNeededThreaded();
    // Fills the buffer with the requested number of audio samples, or the max available if lower
    void GetInputDataThreaded(Zero::Array<float>& buffer, unsigned howManySamples);
    // Sets whether the system should use a low or high latency value
    void SetOutputLatency(LatencyValues::Enum latency);

    // Ring buffer used for mixed output
    RingBuffer OutputRingBuffer;

    // The following two functions are called from the audio IO thread using the callback

    // Gets the mixed buffer that is ready to output
    void GetMixedOutputSamples(float* outputBuffer, const unsigned frames);
    // Saves the input buffer from the microphone
    void SaveInputSamples(const float* inputBuffer, unsigned frames);

  private:
    // Object to handle OS-specific audio input and output
    AudioInputOutput AudioIO;
    // Buffer used for the OutputRingBuffer
    float* MixedOutputBuffer;
    // The number of mix buffer frames for each latency setting
    unsigned OutputBufferSizePerLatency[LatencyValues::Size];
    // Current latency setting for the audio output
    LatencyValues::Enum mOutputStreamLatency;
    // Size of the buffer for input data
    static const unsigned InputBufferSize = 8192;
    // Buffer of input data
    float InputBuffer[InputBufferSize];
    // Ring buffer used for receiving input data
    RingBuffer InputRingBuffer;
    // For notifying the mix thread when a new buffer is needed.
    Zero::Semaphore MixThreadSemaphore;
    // List of info objects for each stream type
    StreamInfo StreamInfoList[StreamTypes::Size];
    // The multiplier used to find the mix frames for a certain sample rate
    const float BufferSizeMultiplier = 0.04f;
    // The value used to start calculating the mix frames
    const unsigned BufferSizeStartValue = 512;
    // Last error message pertaining to the audio API
    Zero::String mApiErrorMessage;

    // Sets variables and initializes output buffers at the appropriate size
    void InitializeOutputBuffers();
    // Creates output buffers using the specified size
    void SetUpOutputBuffers();
  };

}

#endif
