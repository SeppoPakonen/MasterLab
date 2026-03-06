/*
    SPDX-FileCopyrightText: 2011-2014 Meltytech LLC
    SPDX-FileCopyrightText: 2011-2014 Dan Dennedy <dan@dennedy.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_monitor_VideoWidget_h_
#define _Cool_monitor_VideoWidget_h_

#include <CtrlLib/CtrlLib.h>
#include "../Definitions.h"

namespace Mlt {
    class Filter;
    class Producer;
    class Consumer;
}

NAMESPACE_UPP

class VideoWidget : public ParentCtrl {
public:
    typedef VideoWidget CLASSNAME;

    VideoWidget();
    virtual ~VideoWidget();

    // Rendering control
    void StartGlsl();
    void StopGlsl();
    void Clear();
    
    // MLT integration
    std::shared_ptr<::Mlt::Consumer> GetConsumer() { return consumer; }
    ::Mlt::Producer* GetProducer() { return producer.get(); }
    
    // Accessors
    float GetZoom() const { return zoom; }
    void  SetZoom(float z) { zoom = z; Refresh(); }
    
    // State
    bool IsReady() const { return is_initialized; }
    
    // Logic
    void RequestRefresh(bool slow_refresh = false);
    void Stop();
    void Restart();

protected:
    virtual void Paint(Draw& draw) override;
    virtual void Layout() override;

private:
    std::shared_ptr<::Mlt::Consumer> consumer;
    std::shared_ptr<::Mlt::Producer> producer;
    
    float zoom = 1.0f;
    bool  is_initialized = false;
    
    void InitializeMLT();
};

END_UPP_NAMESPACE

#endif
