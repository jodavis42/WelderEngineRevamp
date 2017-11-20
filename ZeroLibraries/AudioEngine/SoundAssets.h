///////////////////////////////////////////////////////////////////////////////
///
/// Author: Andrea Ellinger
/// Copyright 2017, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef ASSETS_H
#define ASSETS_H

#define WAVE_VOLUME 0.5f

struct OpusDecoder;

namespace Audio
{
  //------------------------------------------------------------------------------------- Frame Data

  struct FrameData
  {
    /** Number of channels in this sound. */
    unsigned HowManyChannels;
    /** Array of sample values for this frame. */
    float Samples[MaxChannels];
  };

  //------------------------------------------------------------------------------- Sound Asset Node

  // Base class for all sound assets
  class SoundAssetNode
  {
  public:
    SoundAssetNode(ExternalNodeInterface* externalInterface, const bool threaded);

    // Sets the external interface pointer
    // If set to NULL and there are no references, asset will be deleted
    void SetExternalInterface(ExternalNodeInterface* externalInterface);
    // Returns true if there are sound instances currently active
    bool IsPlaying();
    // Asset name is stored so that it can be retrieved from a SoundInstance
    Zero::String Name;

  protected:
    virtual ~SoundAssetNode();

    // Pointer to the threaded asset (will be NULL on the threaded object)
    SoundAssetNode* ThreadedAsset;
    // True if this is the threaded asset
    const bool Threaded;

  private:
    // Called when a non-threaded sound instance is created. Returns false if the instance
    // can't be attached to this asset (such as already streaming one instance)
    bool AddReference();
    // Called when a non-threaded sound instance is deleted. If 0 references and no external
    // interface, the asset will be deleted
    void ReleaseReference();

    // Returns the samples for the audio frame at the specified frame index
    virtual FrameData GetFrame(const unsigned frameIndex) = 0;
    // Fills the provided buffer with samples, starting at the specified frame index
    virtual void GetBuffer(float* buffer, const unsigned frameIndex, const unsigned numberOfSamples) = 0;
    // Returns the number of audio channels
    virtual unsigned GetChannels() = 0;
    // The total number of audio frames in this asset's data
    virtual unsigned GetNumberOfFrames() = 0;
    // Returns true if this asset is streaming
    virtual bool GetStreaming() = 0;
    // Returns true if another instance can be added to this asset
    // Called from AddReference
    virtual bool OkayToAddInstance() { return true; }
    // Called from ReleaseReference
    virtual void RemoveInstance() {}
    // Resets a streaming file back to the beginning
    virtual void ResetStreamingFile() {}

    // Pointer to the external interface object for this asset
    ExternalNodeInterface* ExternalData;
    // Number of existing references from sound instances
    unsigned ReferenceCount;

    Zero::Link<SoundAssetNode> link;

    friend class SoundInstanceNode;
    friend class AudioSystemInternal;
  };

  //-------------------------------------------------------------------------- Sound Asset From File

  class FileDecoder;
  
  class SoundAssetFromFile : public SoundAssetNode
  {
  public:
    SoundAssetFromFile(Zero::Status& status, const Zero::String& fileName, const bool streaming,
      ExternalNodeInterface* externalInterface, const bool isThreaded = false);

    // The total number of audio frames in this asset's data
    unsigned GetNumberOfFrames() override;
    // Returns true if this asset is streaming
    bool GetStreaming() override;
    // Resets a streaming file back to the beginning
    void ResetStreamingFile() override;
    // Returns the length of the audio file, in seconds
    float GetLengthOfFile();
    // Returns the number of channels in the audio data
    unsigned GetChannels() override;
        
  private:
    ~SoundAssetFromFile();

    // Returns the samples for the audio frame at the specified index
    FrameData GetFrame(const unsigned frameIndex) override;
    // Fills the provided buffer with samples, starting at the specified index
    void GetBuffer(float* buffer, const unsigned frameIndex, const unsigned numberOfSamples) override;
    // Returns false if this is a streaming asset and there is already an instance associated with it
    bool OkayToAddInstance() override;
    // Resets the HasStreamingInstance variable
    void RemoveInstance() override;
    // Checks if there is a decoded packet to copy into the Samples buffer
    void CheckForDecodedPacket();

    // If true, this is a streaming asset
    bool Streaming;
    // If true, the asset is streaming and has an instance associated with it
    bool HasStreamingInstance;
    // The length of the audio file, in seconds
    float FileLength;
    // The number of channels in the audio data
    unsigned Channels;
    // The number of audio frames in the audio data
    unsigned FrameCount;
    // Pointer to the decoder object used by this asset
    FileDecoder* Decoder;
    // The index of the first undecoded sample (the first index that can't be used yet)
    unsigned UndecodedSamplesIndex;
    // The buffer of decoded samples
    float* Samples;
    // If streaming, keeps track of previous samples
    unsigned PreviousBufferSamples;
    // The next buffer of decoded streamed samples
    float* NextStreamedSamples;
    // If true, the NextStreamedSamples buffer needs to be filled out
    bool NeedSecondBuffer;
    // Used to check when to get a decoded packet
    unsigned IndexCheck;
  };


  //--------------------------------------------------------------------- Generated Wave Sound Asset

  class GeneratedWaveSoundAsset : public SoundAssetNode
  {
  public:
    GeneratedWaveSoundAsset(const OscillatorTypes::Enum waveType, const float frequency, 
      ExternalNodeInterface *extInt, const bool isThreaded = false);

    // Returns the number of channels in the audio data
    unsigned GetChannels() override { return 1; }
    // The total number of audio frames in this asset's data
    unsigned GetNumberOfFrames() override;
    // Returns true if this asset is streaming
    bool GetStreaming() override;
    // Returns the current frequency of the generated wave
    float GetFrequency();
    // Sets the frequency of the generated wave, over a specified number of seconds
    void SetFrequency(const float frequency, const float time);
    // If a square wave is chosen, set the fraction (0 - 1.0) of the wave which will be positive
    void SetSquareWavePositiveFraction(float positiveFraction);

  private:
    ~GeneratedWaveSoundAsset();

    // Returns the samples for the audio frame at the specified index
    FrameData GetFrame(const unsigned frameIndex) override;
    // Fills the provided buffer with samples, starting at the specified index
    void GetBuffer(float* buffer, const unsigned frameIndex, const unsigned numberOfSamples) override;

    Oscillator* WaveData;
    // The current wave frequency
    float Frequency;
    // Used to interpolate between two frequencies
    InterpolatingObject FrequencyInterpolator;
  };
}

#endif