#ifndef PROBLEM_H
#define	PROBLEM_H

class Problem {
public:
    Problem() {}
    virtual void print() const = 0;
    virtual ~Problem() {}
};

typedef Problem * create_t();
typedef void destroy_t(Problem *);

#endif	/* PROBLEM_H */

