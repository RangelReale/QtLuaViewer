#include <LuaStateWidget.h>

#include <QTreeWidgetItem>
#include <QHeaderView>
#include <QResizeEvent>

LuaStateWidget::LuaStateWidget(QWidget *parent) :
	QWidget(parent), _maxlevels(4)
{
	_tree = new QTreeWidget(this);
	_tree->setGeometry(0, 0, 800, 600);
	_tree->setColumnCount(2);
	_tree->setColumnWidth(0, 200);
	_tree->setColumnWidth(1, 200);
	_tree->setHeaderLabels(QStringList() << "Name" << "Value");
}

void LuaStateWidget::update(LuaIntf::LuaRef ref, int maxlevels)
{
	_tree->clear();
	_ref = ref;
	_maxlevels = maxlevels;
	addTable(nullptr, _ref);
}

void LuaStateWidget::addTable(QTreeWidgetItem *parent, LuaIntf::LuaRef &table, int level)
{
	if (level > _maxlevels) return;

	if (table.type() == LuaIntf::LuaTypeID::TABLE)
	{
		for (auto i = table.begin(); i != table.end(); ++i)
		{
			addItem(parent, luarefToString(i.key()), i.value(), level);
		}
	}
}

void LuaStateWidget::addItem(QTreeWidgetItem *parent, const QString &name, LuaIntf::LuaRef &item, int level)
{
	QStringList strings;
	strings.append(name);
	strings.append(luarefToString(item));

	QTreeWidgetItem *newitem = new QTreeWidgetItem(strings);
	if (parent)
		parent->addChild(newitem);
	else
		_tree->addTopLevelItem(newitem);

	if (name == "_G") 
		return;

	LuaIntf::LuaRef mt = item.getMetaTable();
	if (mt && mt != item)
		addItem(newitem, "_mt", mt);

	addTable(newitem, item, level+1);
}

QString LuaStateWidget::luarefToString(const LuaIntf::LuaRef &item)
{
	switch (item.type())
	{
	case LuaIntf::LuaTypeID::BOOLEAN:
		return item.toValue<bool>() ? "true" : "false";
	case LuaIntf::LuaTypeID::FUNCTION:
		return "[function]";
	case LuaIntf::LuaTypeID::LIGHTUSERDATA:
		return "[lightuserdata]";
	case LuaIntf::LuaTypeID::NIL:
		return "[nil]";
	case LuaIntf::LuaTypeID::NONE:
		return "[none]";
	case LuaIntf::LuaTypeID::NUMBER:
		return QString("%1").arg(item.toValue<double>());
	case LuaIntf::LuaTypeID::STRING:
		return QString::fromStdString(item.toValue<std::string>());
	case LuaIntf::LuaTypeID::TABLE:
		return "[table]";
	case LuaIntf::LuaTypeID::THREAD:
		return "[thread]";
	case LuaIntf::LuaTypeID::USERDATA:
		return "[userdata]";
	default:
		return "[unknown]";
	}
}

void LuaStateWidget::resizeEvent(QResizeEvent * event)
{
	QWidget::resizeEvent(event);
	_tree->resize(event->size());
}

