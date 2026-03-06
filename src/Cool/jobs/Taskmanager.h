/*
    SPDX-FileCopyrightText: 2021 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_jobs_TaskManager_h_
#define _Cool_jobs_TaskManager_h_

#include "Abstracttask.h"

NAMESPACE_UPP

enum class TaskManagerStatus { NoJob, Pending, Running, Finished, Canceled };

class TaskManager {
public:
    TaskManager();
    virtual ~TaskManager();

    void DiscardJobs(const ObjectId& owner, AbstractTask::JOBTYPE type = AbstractTask::NOJOBTYPE, 
                     bool soft_delete = false, const Vector<AbstractTask::JOBTYPE>& exceptions = {});
    void DiscardJob(const ObjectId& owner, const String& uuid);
    void DiscardJobsByType(AbstractTask::JOBTYPE job_type);

    bool HasPendingJob(const ObjectId& owner, AbstractTask::JOBTYPE type = AbstractTask::NOJOBTYPE) const;
    TaskManagerStatus GetJobStatus(const ObjectId& owner) const;
    int GetJobProgressForClip(const ObjectId& owner);

    void StartTask(int owner_id, AbstractTask* task);
    void TaskDone(int cid, AbstractTask* task);

    bool IsBlocked() const { return block_updates; }
    void UnBlock() { block_updates = false; }

private:
    // U++ handles threading via CoWork or custom pools
    std::unordered_map<int, std::vector<AbstractTask*>> task_list;
    mutable Mutex tasks_lock;
    bool block_updates = false;
};

END_UPP_NAMESPACE

#endif
