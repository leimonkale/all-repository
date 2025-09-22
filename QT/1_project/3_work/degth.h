#ifndef DEGTH_H
#define DEGTH_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Degth;
}
QT_END_NAMESPACE

class Degth : public QMainWindow
{
    Q_OBJECT

public:
    Degth(QWidget *parent = nullptr);
    ~Degth();

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_13_clicked();

    void incrementFlag(const char *a) {
            if (a == nullptr) return; // 避免空指针
            int len = strlen(a); // 获取字符串实际长度（字节数）
            // 检查数组是否有足够空间（防止越界）
            if (flag + len >= 1024) {
                // 处理空间不足的情况（如截断或提示）
                return;
            }
            // 复制整个字符串到 enter 数组
            for (int i = 0; i < len; i++) {
                enter[flag + i] = a[i];
            }
            flag += len; // 移动指针到下一个空闲位置
    }

    void updateLineEdit();

    void on_pushButton_17_clicked();

    void clearEnterArray() {
        memset(enter, 0, sizeof(enter));
    }

    char* calculateAndGetResult() {
        memset(resultBuffer, 0, sizeof(resultBuffer));

        // 1. 验证输入有效性
        if (flag == 0) {
            strncpy(resultBuffer, "error", sizeof(resultBuffer)-1);
            return resultBuffer;
        }

        // 2. 确保enter数组以\0结尾
        enter[flag] = '\0';
        QString expression = QString::fromUtf8(enter);

        // 3. 查找运算符并分割数字
        int opPos = -1;
        char op = '\0';
        const QString ops = "+-*/";
        for (int i = 1; i < expression.length(); ++i) {
            if (ops.contains(expression[i])) {
                opPos = i;
                op = expression[i].toLatin1();
                break;
            }
        }
        if (opPos == -1) {
            strncpy(resultBuffer, "error", sizeof(resultBuffer)-1);
            return resultBuffer;
        }

        // 4. 转换数字到firstnumber和secondenumber
        QString num1Str = expression.left(opPos);
        QString num2Str = expression.mid(opPos + 1);
        bool ok1, ok2;
        firstnumber = num1Str.toDouble(&ok1);
        secondenumber = num2Str.toDouble(&ok2);

        if (!ok1 || !ok2) {
            strncpy(resultBuffer, "error", sizeof(resultBuffer)-1);
            return resultBuffer;
        }

        // 5. 执行运算
        double result;
        switch (op) {
        case '+':
            result = firstnumber + secondenumber;
            break;
        case '-':
            result = firstnumber - secondenumber;
            break;
        case '*':
            result = firstnumber * secondenumber;
            break;
        case '/':
            if (qFuzzyCompare(secondenumber, 0.0)) {
                strncpy(resultBuffer, "error", sizeof(resultBuffer)-1);
                return resultBuffer;
            }
            result = firstnumber / secondenumber;
            break;
        default:
            strncpy(resultBuffer, "error", sizeof(resultBuffer)-1);
            return resultBuffer;
        }

        // 6. 格式化结果为字符串（存入resultBuffer）
        if (result == floor(result)) {
            // 整数结果
            snprintf(resultBuffer, sizeof(resultBuffer), "%lld", (long long)result);
        } else {
            // 小数结果
            snprintf(resultBuffer, sizeof(resultBuffer), "%g", result);
        }

        return resultBuffer;
    }


private:
    Ui::Degth *ui;

    int flag = 0;
    char enter[1024];
    double firstnumber;
    double secondenumber;
    char resultBuffer[1024];
};
#endif // DEGTH_H
