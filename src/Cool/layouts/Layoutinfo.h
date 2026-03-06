#ifndef _Cool_layouts_Layoutinfo_h_
#define _Cool_layouts_Layoutinfo_h_

#include "../Cool.h"

NAMESPACE_UPP

/**
 * @class LayoutInfo
 * @brief Holds information about a UI layout
 */
struct LayoutInfo
{
    QString internalId;  // Internal ID like "kdenlive_editing"
    QString displayName; // User specified name or for default layouts this we be the translated name like "Editing"
    QString path;        // The path to the json layout
    QString verticalPath; // The path to the json vertical layout
    bool readOnly;       // True if this is a default layout that cannot be deleted

    /**
     * @brief Constructor
     * @param id The internal ID
     * @param name The display name
     */
    LayoutInfo(const QString &id = QString(), const QString &name = QString())
        : internalId(id)
        , displayName(name)
        , path(QString())
        , verticalPath(QString())
        , readOnly(false)
    {
    }

    /**
     * @brief Check if the layout has valid data
     */
    bool isValid() const { return !internalId.IsEmpty() && (!path.IsEmpty() || !verticalPath.IsEmpty()); }
    bool hasHorizontalData() const { return !path.IsEmpty(); }
    bool hasVerticalData() const { return !verticalPath.IsEmpty(); }
};

END_UPP_NAMESPACE

#endif
