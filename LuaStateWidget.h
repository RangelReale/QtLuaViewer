#ifndef H__LUASTATEWIDGET__H
#define H__LUASTATEWIDGET__H

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "LuaIntf/LuaIntf.h"

#include <QWidget>
#include <QTreeWidget>

class LuaStateWidget : public QWidget
{
public:
	LuaStateWidget(QWidget *parent = NULL);

	void update(LuaIntf::LuaRef ref, int maxlevels = 4);
protected:
	void resizeEvent(QResizeEvent * event);
private:
	void addTable(QTreeWidgetItem *parent, LuaIntf::LuaRef &table, int level = 0);
	void addItem(QTreeWidgetItem *parent, const QString &name, LuaIntf::LuaRef &item, int level = 0);

	QString luarefToString(const LuaIntf::LuaRef &item);

	QTreeWidget *_tree;
	LuaIntf::LuaRef _ref;
	int _maxlevels;
};


#endif // H__LUASTATEWIDGET__H