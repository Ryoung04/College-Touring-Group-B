#ifndef COLLEGETOURPAGE_H
#define COLLEGETOURPAGE_H

#include <QMainWindow>

namespace Ui {
class collegetourpage;
}

class collegetourpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit collegetourpage(QWidget *parent = nullptr);
    ~collegetourpage();

private:
    Ui::collegetourpage *ui;
};

#endif // COLLEGETOURPAGE_H
