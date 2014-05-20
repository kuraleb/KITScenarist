#ifndef SCENARIONAVIGATORITEMDELEGATE_H
#define SCENARIONAVIGATORITEMDELEGATE_H

#include <QStyledItemDelegate>


namespace UserInterface
{
	class ScenarioNavigatorItemWidget;

	/**
	 * @brief Делегат для отрисовки элементов навигатора
	 */
	class ScenarioNavigatorItemDelegate : public QStyledItemDelegate
	{
		Q_OBJECT

	public:
		explicit ScenarioNavigatorItemDelegate(QObject* _parent = 0);
		~ScenarioNavigatorItemDelegate();

		void paint (QPainter* _painter, const QStyleOptionViewItem& _option, const QModelIndex& _index) const;
		QSize sizeHint(const QStyleOptionViewItem& _option, const QModelIndex& _index) const;

		/**
		 * @brief Настроить отображение номера сцены
		 */
		void setShowSceneNumber(bool _show);

	private:
		/**
		 * @brief Виджет для отрисовки элементов навигатора
		 */
		ScenarioNavigatorItemWidget* m_itemWidget;

		/**
		 * @brief Отображать номер сцены
		 */
		bool m_showSceneNumber;
	};
}

#endif // SCENARIONAVIGATORITEMDELEGATE_H