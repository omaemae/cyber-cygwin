#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <QAbstractListModel>
#include "applicationitem.h"
#include "systemappmonitor.h"
#include "xwindowinterface.h"

class ApplicationModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        AppIdRole = Qt::UserRole + 1,
        IconNameRole,
        VisibleNameRole,
        ActiveRole,
        WindowCountRole,
        IsPinnedRole
    };

    explicit ApplicationModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void save() { savePinAndUnPinList(); }

    Q_INVOKABLE void clicked(const QString &id);
    Q_INVOKABLE void raiseWindow(const QString &id);

    Q_INVOKABLE bool openNewInstance(const QString &appId);
    Q_INVOKABLE void closeAllByAppId(const QString &appId);
    Q_INVOKABLE void pin(const QString &appId);
    Q_INVOKABLE void unPin(const QString &appId);

    Q_INVOKABLE void updateGeometries(const QString &id, QRect rect);

    Q_INVOKABLE void move(int from, int to);

signals:
    void countChanged();

private:
    ApplicationItem *findItemByWId(quint64 wid);
    ApplicationItem *findItemById(const QString &id);
    bool contains(const QString &id);
    int indexOf(const QString &id);
    void initPinnedApplications();
    void savePinAndUnPinList();

    void handleDataChangedFromItem(ApplicationItem *item);

    void onWindowAdded(quint64 wid);
    void onWindowRemoved(quint64 wid);
    void onActiveChanged(quint64 wid);

private:
    XWindowInterface *m_iface;
    SystemAppMonitor *m_sysAppMonitor;
    QList<ApplicationItem *> m_appItems;
};

#endif // APPLICATIONMODEL_H
