#ifndef LIBALGORYTHM_H
#define LIBALGORYTHM_H
#include <QList>


class _2values
{
public:
    _2values(int index);

    double get1();
    double get2();
    int getIndex();
    void set1(double value);
    void set2(double value);


private:
    double valeur1;
    double valeur2;
    int ind;
};


class Algorythm
{
public:
    Algorythm();
    void setValues(QList<_2values *> *tableau);
    QList<int> Trier(bool decroissant=true);
private:
    QList<_2values *> *tab;
};


#endif // LIBALGORYTHM_H
