#pragma once

#include "common.h"
#include <xaudio2.h>

class xaudio_player : private IXAudio2VoiceCallback {
private:
    com_ptr<IXAudio2> _xaudio;
    IXAudio2MasteringVoice* _mastering_voice;
    IXAudio2SourceVoice* _source_voice;

public:
    xaudio_player();
    ~xaudio_player();

    HRESULT initialize(const WAVEFORMATEX& wfx);
    void finalize();

    [[nodiscard]] bool is_initialized() const
    {
        return _xaudio != nullptr && _mastering_voice != nullptr && _source_voice != nullptr;
    }

    HRESULT start();
    HRESULT stop();

    [[nodiscard]] XAUDIO2_VOICE_STATE get_voice_state() const;
    [[nodiscard]] float get_volume() const;
    HRESULT set_volume(float volume);

private:
    void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 BytesRequired) override;
    void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() override;
    void STDMETHODCALLTYPE OnStreamEnd() override;
    void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext) override;
    void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext) override;
    void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext) override;
    void STDMETHODCALLTYPE OnVoiceError(void* pBufferContext, HRESULT Error) override;
};