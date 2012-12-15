#include "arclength.h"
#include <assert.h>

#define MODULUS(x) (x<0?-x:x)

ArcLength::ArcLength(Curve* to_parameterize) :
    curve_(to_parameterize), precomputed_(false)
{
}

void ArcLength::AdaptativeGaussianPrecalculation() {
    if(precomputed_) return;

    std::vector<double> points;
    std::vector<double> weights;
    acceptable_error_ = 0.0001;

    // ------------ DEFINING GAUSSIAN-LEGENDRE POINTS ---------------------------------
    points.push_back(-0.86113631);
    weights.push_back(0.34785485);

    points.push_back(-0.33998104);
    weights.push_back(0.65214515);

    points.push_back(0.33998104);
    weights.push_back(0.65214515);

    points.push_back(0.86113631);
    weights.push_back(0.34785485);
    // ------------ --------------------------------- ---------------------------------


    precalculated_length_.clear();
    precalculated_length_.push_back(ULength());

    int number_of_slices = 2;
    double slice_size = 1.0/((double)(number_of_slices));
    double last_calculated = 0;

    // Number of slices is the number of mandatory subdivisions for the adaptative method
    // the main interval of integration will be split in this number of slices
    for( int i = 0 ; i < number_of_slices ; i++ ) {

        LengthInterval start;
        start.u_start_ = slice_size*((double)(i));
        start.u_end_ = slice_size*((double)(i+1));
        start.start_length_ = last_calculated;
        start.error_ = acceptable_error_;
        start.length_ = GaussianLegendreToInterval(start.u_start_, start.u_end_, points, weights);


        std::vector<LengthInterval> to_consider;
        to_consider.push_back(start);

        // Main adaptative gaussian integration calculus
        while(!to_consider.empty()) {
            LengthInterval current = to_consider[0];
            to_consider.erase(to_consider.begin());

            double midpoint = (current.u_start_ + current.u_end_)/2.0;

            double first_interval_integral = GaussianLegendreToInterval(current.u_start_, midpoint, points, weights);
            double second_interval_integral = GaussianLegendreToInterval(midpoint, current.u_end_, points, weights);

            if( current.length_ - first_interval_integral - second_interval_integral > current.error_ ) {
                LengthInterval interval_a,interval_b;

                interval_a.u_start_ = current.u_start_;
                interval_a.u_end_ = midpoint;
                interval_a.start_length_ = current.start_length_;
                interval_a.length_ = first_interval_integral;

                interval_b.u_start_ = midpoint;
                interval_b.u_end_ = current.u_end_;
                interval_b.start_length_ = current.start_length_ + first_interval_integral;
                interval_b.length_ = second_interval_integral;

                interval_a.error_ = interval_b.error_ = current.error_/2.0;

                to_consider.push_back(interval_a);
                to_consider.push_back(interval_b);

            } else {
                ULength final_size;
                final_size.u_ = current.u_end_;
                final_size.length_ = current.start_length_ + current.length_;
                precalculated_length_.push_back(final_size);
            }
        }
        // Result for this slice
        last_calculated = precalculated_length_[precalculated_length_.size()-1].length_;
    }
    precomputed_ = true;
    total_length_ = precalculated_length_[precalculated_length_.size()-1].length_;

}

qglviewer::Vec ArcLength::GetByNormalizedS(double s) const {
    double real_length = s * total_length_;
    std::cout << "Input: " << s << std::endl;
    return GetByS(real_length);
}

qglviewer::Vec ArcLength::GetByS(double constant_length) const {

    double x0 = constant_length/total_length_;
    double x1;


    double current_result = FunctionToGetRoot(x0,constant_length);
    current_result = MODULUS(current_result);

    std::cout << "f(x0): " << FunctionToGetRoot(x0,constant_length) << std::endl;
    std::cout << "f'(x0): " << NumericalDerivative(x0,constant_length) << std::endl;
    double possible_error = acceptable_error_;

    // Using Newton-Raphson to solve main equation s-Lenght(u1,u2) = 0
    int max_iteration = 20;
    int iteration = 0;
    while( (current_result > possible_error) && (iteration<max_iteration) ) {
        iteration++;
        x1 = x0 - (FunctionToGetRoot(x0,constant_length)/NumericalDerivative(x0,constant_length));
        x0 = x1;

        double new_result = FunctionToGetRoot(x0,constant_length);
        new_result = MODULUS(new_result);

        double delta = new_result - current_result;
        delta = MODULUS(delta);

        if(delta<possible_error) break;

        current_result = new_result;

        std::cout << " / Current X: " << x0 << std::endl;
        std::cout << " / Delta: " << delta << std::endl;
    }

    std::cout << "Lenght Input: " << constant_length << std::endl;
    std::cout << "Lenght Output: " << GetLength(x0) << std::endl;
    std::cout << "Output: " << x0 << std::endl;
    std::cout <<"----------------------------" << std::endl;


    qglviewer::Vec result = curve_->Evaluate(x0);
    return result;
}

double ArcLength::GetLength(double t) const {

    int s = 0;
    int e = precalculated_length_.size()-1;

    while(s<e){
        if(e-s == 1) break;

        int m = (s+e)/2;
        ULength current = precalculated_length_.at(m);
        if(current.u_ > t ){
            e = m;
        }else{
            s = m;
        }
    }

    std::vector<double> points;
    std::vector<double> weights;

    // ------------ DEFINING GAUSSIAN-LEGENDRE POINTS ---------------------------------
    points.push_back(-0.86113631);
    weights.push_back(0.34785485);

    points.push_back(-0.33998104);
    weights.push_back(0.65214515);

    points.push_back(0.33998104);
    weights.push_back(0.65214515);

    points.push_back(0.86113631);
    weights.push_back(0.34785485);
    // ------------ --------------------------------- ---------------------------------

    ULength ps = precalculated_length_[s];
    double result = ps.length_ + GaussianLegendreToInterval(ps.u_, t, points, weights);
    return result;
}

double ArcLength::GetTotalLength() const {
    return total_length_;
}

double ArcLength::FunctionToGetRoot(double x, double constant_length) const {
    return constant_length - GetLength(x);
}

double ArcLength::NumericalDerivative(double x, double constant_length) const {
    double h = 0.01;
    bool finished = false;
    while(!finished){
        finished = true;
        if(x-h >=0.0 && x+h<=1.0)
            return (FunctionToGetRoot(x+h,constant_length) - FunctionToGetRoot(x-h,constant_length))/(2.0*h);
        else if(x-h >=0.0)
            return (FunctionToGetRoot(x,constant_length) - FunctionToGetRoot(x-h,constant_length))/(h);
        else if(x+h<=1.0)
            return (FunctionToGetRoot(x+h,constant_length) - FunctionToGetRoot(x,constant_length))/(h);
        else
            finished = false;
        h = h/10.0;
    }
    // Could not do a numerical derivation
    return 0.0;
}

qglviewer::Vec ArcLength::NumericalVectorDerivative(double x) const {
    double h = 0.01;
    bool finished = false;
    while(!finished){
        finished = true;
        if(x-h >=0.0 && x+h<=1.0)
            return (curve_->Evaluate(x+h) - curve_->Evaluate(x-h))/(2.0*h);
        else if(x-h >=0.0)
            return (curve_->Evaluate(x) - curve_->Evaluate(x-h))/(h);
        else if(x+h<=1.0)
            return (curve_->Evaluate(x+h) - curve_->Evaluate(x))/(h);
        else
            finished = false;
        h = h/10.0;
    }
    // Could not do a numerical derivation
    return qglviewer::Vec();
}

double ArcLength::GaussianLegendreToInterval(double a, double b, std::vector<double>& points, std::vector<double>& weights) const {
    double interval_constant = (b-a)/2.0;
    //
    double integral = 0;
    for(size_t i = 0 ; i < points.size() ; i++ ) {
        double parametized_input = ((b-a)*points[i] + b + a)/2;
        integral += (weights[i]*(NumericalVectorDerivative(parametized_input).norm()));
    }

    return interval_constant*integral;
}
