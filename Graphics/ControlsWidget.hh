#pragma once
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>

class ControlsWidget : public QWidget {
public:
  ControlsWidget(std::initializer_list<const char *> labels,
                 QWidget *parent = nullptr)
      : QWidget(parent), layout(this) {

    setStyleSheet("background-color: transparent;");
    setAttribute(Qt::WA_TransparentForMouseEvents);

    size_t i(0);
    for (auto label : labels) {
      std::unique_ptr<QLabel> text(new QLabel(label));
      layout.addWidget(text.get(), i / 2, i % 2);
      this->labels.push_back(std::move(text));
      ++i;
    }

    layout.setColumnStretch(0, 0);
    layout.setColumnStretch(1, 1);
  }

private:
  QGridLayout layout;
  std::vector<std::unique_ptr<QLabel>> labels;
};
