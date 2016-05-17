#include "../include/type_traits.hpp"

#define BOOST_TEST_MODULE pagmo_type_traits_test
#include <boost/test/unit_test.hpp>

#include <string>
#include <utility>
#include <vector>

#include "../include/types.hpp"

using namespace pagmo;

// No fitness.
struct f_00 {};

// Various types of wrong fitness.
struct f_01
{
    void fitness();
};

struct f_02
{
    void fitness(const vector_double &);
};

struct f_03
{
    vector_double fitness(const vector_double &);
};

struct f_04
{
    vector_double fitness(vector_double &) const;
};

// Good one.
struct f_05
{
    vector_double fitness(const vector_double &) const;
};



BOOST_AUTO_TEST_CASE(has_fitness_test)
{
    BOOST_CHECK((!has_fitness<f_00>::value));
    BOOST_CHECK((!has_fitness<f_01>::value));
    BOOST_CHECK((!has_fitness<f_02>::value));
    BOOST_CHECK((!has_fitness<f_03>::value));
    BOOST_CHECK((!has_fitness<f_04>::value));
    BOOST_CHECK((has_fitness<f_05>::value));
}

// No fitness.
struct no_00 {};

// Various types of wrong get_nobj.
struct no_01
{
    vector_double::size_type get_nobj();
};

struct no_02
{
    int get_nobj() const;
};

// Good one.
struct no_03
{
    vector_double::size_type get_nobj() const;
};

BOOST_AUTO_TEST_CASE(has_get_nobj_test)
{
    BOOST_CHECK((!has_fitness<no_00>::value));
    BOOST_CHECK((!has_fitness<no_01>::value));
    BOOST_CHECK((!has_fitness<no_02>::value));
    BOOST_CHECK((!has_fitness<no_03>::value));
}

struct db_00
{};

// The good one.
struct db_01
{
    std::pair<vector_double,vector_double> get_bounds() const;
};

struct db_02
{
    std::pair<vector_double,vector_double> get_bounds();
};

struct db_03
{
    vector_double get_bounds() const;
};

struct db_04
{
};

BOOST_AUTO_TEST_CASE(has_bounds_test)
{
    BOOST_CHECK((!has_bounds<db_00>::value));
    BOOST_CHECK((has_bounds<db_01>::value));
    BOOST_CHECK((!has_bounds<db_02>::value));
    BOOST_CHECK((!has_bounds<db_03>::value));
    BOOST_CHECK((!has_bounds<db_04>::value));
}

struct c_00
{};

// The good one.
struct c_01
{
    vector_double::size_type get_nec() const;
    vector_double::size_type get_nic() const;
};

struct c_02
{
    vector_double::size_type get_nec();
    vector_double::size_type get_nic() const;
};

struct c_03
{
    int get_nec() const;
    vector_double::size_type get_nic() const;
};

struct c_04
{
    vector_double::size_type get_nec() const;
    vector_double::size_type get_nic();
};

struct c_05
{
    vector_double::size_type get_nec() const;
    void get_nic() const;
};

struct c_06
{
    vector_double::size_type get_nec() const;
};

struct c_07
{
    vector_double::size_type get_nic() const;
};

BOOST_AUTO_TEST_CASE(has_e_constraints_test)
{
    BOOST_CHECK((!has_e_constraints<c_00>::value));
    BOOST_CHECK((has_e_constraints<c_01>::value));
    BOOST_CHECK((!has_e_constraints<c_02>::value));
    BOOST_CHECK((!has_e_constraints<c_03>::value));
    BOOST_CHECK((has_e_constraints<c_04>::value));
    BOOST_CHECK((has_e_constraints<c_05>::value));
    BOOST_CHECK((has_e_constraints<c_06>::value));
    BOOST_CHECK((!has_e_constraints<c_07>::value));
}

BOOST_AUTO_TEST_CASE(has_i_constraints_test)
{
    BOOST_CHECK((!has_i_constraints<c_00>::value));
    BOOST_CHECK((has_i_constraints<c_01>::value));
    BOOST_CHECK((has_i_constraints<c_02>::value));
    BOOST_CHECK((has_i_constraints<c_03>::value));
    BOOST_CHECK((!has_i_constraints<c_04>::value));
    BOOST_CHECK((!has_i_constraints<c_05>::value));
    BOOST_CHECK((!has_i_constraints<c_06>::value));
    BOOST_CHECK((has_i_constraints<c_07>::value));
}

struct n_00 {};

// The good one.
struct n_01
{
    std::string get_name() const;
};

struct n_02
{
    std::string get_name();
};

struct n_03
{
    void get_name() const;
};

BOOST_AUTO_TEST_CASE(has_name_test)
{
    BOOST_CHECK((!has_name<n_00>::value));
    BOOST_CHECK((has_name<n_01>::value));
    BOOST_CHECK((!has_name<n_02>::value));
    BOOST_CHECK((!has_name<n_03>::value));
}

struct ei_00 {};

// The good one.
struct ei_01
{
    std::string get_extra_info() const;
};

struct ei_02
{
    std::string get_extra_info();
};

struct ei_03
{
    void get_extra_info() const;
};

BOOST_AUTO_TEST_CASE(has_extra_info_test)
{
    BOOST_CHECK((!has_extra_info<ei_00>::value));
    BOOST_CHECK((has_extra_info<ei_01>::value));
    BOOST_CHECK((!has_extra_info<ei_02>::value));
    BOOST_CHECK((!has_extra_info<ei_03>::value));
}

struct grad_00 {};

// The good one.
struct grad_01
{
    vector_double gradient(const vector_double &) const;
};

struct grad_02
{
    vector_double gradient(const vector_double &);
};

struct grad_03
{
    vector_double gradient(vector_double &) const;
};

struct grad_04
{
    void gradient(const vector_double &) const;
};

BOOST_AUTO_TEST_CASE(has_gradient_test)
{
    BOOST_CHECK((!has_gradient<grad_00>::value));
    BOOST_CHECK((has_gradient<grad_01>::value));
    BOOST_CHECK((!has_gradient<grad_02>::value));
    BOOST_CHECK((!has_gradient<grad_03>::value));
    BOOST_CHECK((!has_gradient<grad_04>::value));
}

struct ov_grad_00 {};

// The good one.
struct ov_grad_01
{
    bool has_gradient() const;
};

struct ov_grad_02
{
    bool has_gradient();
};

struct ov_grad_03
{
    void has_gradient() const;
};

BOOST_AUTO_TEST_CASE(override_has_gradient_test)
{
    BOOST_CHECK((!override_has_gradient<ov_grad_00>::value));
    BOOST_CHECK((override_has_gradient<ov_grad_01>::value));
    BOOST_CHECK((!override_has_gradient<ov_grad_02>::value));
    BOOST_CHECK((!override_has_gradient<ov_grad_03>::value));
}

struct gs_00 {};

// The good one.
struct gs_01
{
    sparsity_pattern gradient_sparsity() const;
};

struct gs_02
{
    sparsity_pattern gradient_sparsity();
};

struct gs_03
{
    int gradient_sparsity() const;
};

BOOST_AUTO_TEST_CASE(has_gradient_sparsity_test)
{
    BOOST_CHECK((!has_gradient_sparsity<gs_00>::value));
    BOOST_CHECK((has_gradient_sparsity<gs_01>::value));
    BOOST_CHECK((!has_gradient_sparsity<gs_02>::value));
    BOOST_CHECK((!has_gradient_sparsity<gs_03>::value));
}

struct hess_00 {};

// The good one.
struct hess_01
{
    std::vector<vector_double> hessians(const vector_double &) const;
};

struct hess_02
{
    std::vector<vector_double> hessians(const vector_double &);
};

struct hess_03
{
    std::vector<vector_double> hessians(vector_double &) const;
};

struct hess_04
{
    void hessians(const vector_double &) const;
};

BOOST_AUTO_TEST_CASE(has_hessians_test)
{
    BOOST_CHECK((!has_hessians<hess_00>::value));
    BOOST_CHECK((has_hessians<hess_01>::value));
    BOOST_CHECK((!has_hessians<hess_02>::value));
    BOOST_CHECK((!has_hessians<hess_03>::value));
    BOOST_CHECK((!has_hessians<hess_04>::value));
}

struct ov_hess_00 {};

// The good one.
struct ov_hess_01
{
    bool has_hessians() const;
};

struct ov_hess_02
{
    bool has_hessians();
};

struct ov_hess_03
{
    void has_hessians() const;
};

BOOST_AUTO_TEST_CASE(override_has_hessians_test)
{
    BOOST_CHECK((!override_has_hessians<ov_hess_00>::value));
    BOOST_CHECK((override_has_hessians<ov_hess_01>::value));
    BOOST_CHECK((!override_has_hessians<ov_hess_02>::value));
    BOOST_CHECK((!override_has_hessians<ov_hess_03>::value));
}

struct hs_00 {};

// The good one.
struct hs_01
{
    std::vector<sparsity_pattern> hessians_sparsity() const;
};

struct hs_02
{
    std::vector<sparsity_pattern> hessians_sparsity();
};

struct hs_03
{
    int hessians_sparsity() const;
};

BOOST_AUTO_TEST_CASE(has_hessians_sparsity_test)
{
    BOOST_CHECK((!has_hessians_sparsity<hs_00>::value));
    BOOST_CHECK((has_hessians_sparsity<hs_01>::value));
    BOOST_CHECK((!has_hessians_sparsity<hs_02>::value));
    BOOST_CHECK((!has_hessians_sparsity<hs_03>::value));
}

struct hss_00 {};

// The good one.
struct hss_01
{
    void set_seed(unsigned int);
};

struct hss_02
{
    void set_seed(unsigned int) const;
};

struct hss_03
{
    void set_seed(int);
};

struct hss_04
{
    double set_seed(unsigned int);
};

BOOST_AUTO_TEST_CASE(has_set_seed_test)
{
    BOOST_CHECK((!has_set_seed<hss_00>::value));
    BOOST_CHECK((has_set_seed<hss_01>::value));
    BOOST_CHECK((has_set_seed<hss_02>::value));
    BOOST_CHECK((has_set_seed<hss_03>::value));
    BOOST_CHECK((!has_set_seed<hss_04>::value));
}

struct ov_hss_00 {};

// The good one.
struct ov_hss_01
{
    bool has_set_seed() const;
};

struct ov_hss_02
{
    bool has_set_seed();
};

struct ov_hss_03
{
    void has_set_seed() const;
};

BOOST_AUTO_TEST_CASE(override_has_set_seed_test)
{
    BOOST_CHECK((!override_has_set_seed<ov_hss_00>::value));
    BOOST_CHECK((override_has_set_seed<ov_hss_01>::value));
    BOOST_CHECK((!override_has_set_seed<ov_hss_02>::value));
    BOOST_CHECK((!override_has_set_seed<ov_hss_03>::value));
}

struct hsv_00 {};

// The good one
struct hsv_01
{
    void set_verbosity(unsigned int);
};

// also good
struct hsv_02
{
    void set_verbosity(unsigned int) const;
};

// also good
struct hsv_03
{
    void set_verbosity(int);
};

struct hsv_04
{
    double set_verbosity(unsigned int);
};

BOOST_AUTO_TEST_CASE(has_set_verbose_test)
{
    BOOST_CHECK((!has_set_verbosity<hsv_00>::value));
    BOOST_CHECK((has_set_verbosity<hsv_01>::value));
    BOOST_CHECK((has_set_verbosity<hsv_02>::value));
    BOOST_CHECK((has_set_verbosity<hsv_03>::value));
    BOOST_CHECK((!has_set_verbosity<hsv_04>::value));
}

struct hev_00 {};

// The good one
struct hev_01
{
    population evolve(population) const;
};

struct hev_02
{
    population evolve(const population&);
};

struct hev_03
{
    population evolve(population&) const;
};

struct hev_04
{
    double evolve(const population&) const;
};

struct hev_05
{
    population evolve(const double&) const;
};

BOOST_AUTO_TEST_CASE(has_evolve_test)
{
    BOOST_CHECK((!has_evolve<hev_00>::value));
    BOOST_CHECK((has_evolve<hev_01>::value));
    BOOST_CHECK((!has_evolve<hev_02>::value));
    BOOST_CHECK((!has_evolve<hev_03>::value));
    BOOST_CHECK((!has_evolve<hev_04>::value));
    BOOST_CHECK((!has_evolve<hev_05>::value));
}
