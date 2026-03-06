/*
    SPDX-FileCopyrightText: 2021 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_jobs_AbstractTask_h_
#define _Cool_jobs_AbstractTask_h_

#include "../Definitions.h"

NAMESPACE_UPP

class TaskManager;

class AbstractTask {
    friend class TaskManager;

public:
    enum JOBTYPE {
        NOJOBTYPE = 0, PROXYJOB, CUTJOB, STABILIZEJOB, TRANSCODEJOB,
        FILTERCLIPJOB, THUMBJOB, ANALYSECLIPJOB, LOADJOB,
        AUDIOTHUMBJOB, SPEEDJOB, CACHEJOB, MASKJOB, MELTJOB
    };

    AbstractTask(const ObjectId& owner, JOBTYPE type);
    virtual ~AbstractTask();

    virtual void Run() = 0;
    
    const ObjectId& GetOwnerId() const { return owner; }
    JOBTYPE GetType() const { return type; }
    String  GetUuid() const { return uuid; }

protected:
    ObjectId owner;
    int      progress = -1;
    String   description;
    bool     is_successful = false;
    Atomic   is_canceled;
    Atomic   soft_delete;
    Mutex    run_mutex;
    bool     is_force = false;
    bool     is_running = false;
    String   uuid;
    JOBTYPE  type;

    void Cleanup();
};

END_UPP_NAMESPACE

#endif
