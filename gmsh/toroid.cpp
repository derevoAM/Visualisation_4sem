#include <set>
#include <cmath>
#include <cstdlib>
#include <gmsh.h>

int main(int argc, char **argv) {
    gmsh::initialize(argc, argv);

    gmsh::model::add("toroid");

    gmsh::model::occ::addCircle(0, 0, 0, 0.5, 1);
    gmsh::model::occ::addCurveLoop({1}, 1);
    gmsh::model::occ::addCircle(0, 0, 0, 0.4, 2);
    gmsh::model::occ::addCurveLoop({2}, 2);

    std::vector<std::pair<int, int> > ov;
    gmsh::model::occ::addPlaneSurface({1, 2}, 1);
    gmsh::model::occ::synchronize();


    //gmsh::model::occ::extrude({{2, 1}}, 0, 0, 0.3, ov2);

//    gmsh::option::setNumber("Mesh.CharacteristicLengthFromCurvature", 1);
//    gmsh::option::setNumber("Mesh.MinimumElementsPerTwoPi", 1);

    gmsh::model::occ::revolve({{2, 1}}, 1, 0, 0, 0, 1, 0, M_PI, ov, {200}, {},
                              true); //////// Если не ставить количество слоев, то тор не будет замыкаться. Смог сделать незамкнутый тор с треугольной сеткой(numElements{}) и замкнутый с призмовидной сеткой(numElements{x}).
    //gmsh::model::occ::synchronize();
    //gmsh::model::occ::remove({{2, 1}});
    gmsh::model::occ::revolve({{ov[0]}}, 1, 0, 0, 0, 1, 0, M_PI, ov, {200}, {}, true);

    gmsh::model::occ::synchronize();
    gmsh::option::setNumber("Mesh.MeshSizeFromCurvature", 20);

    // We can constraint the min and max element sizes to stay within reasonnable
    // values (see `t10.cpp' for more details):
    gmsh::option::setNumber("Mesh.MeshSizeMin", 0.001);
    gmsh::option::setNumber("Mesh.MeshSizeMax", 0.03);


    gmsh::model::mesh::generate(3);
    gmsh::write("toroid.msh");

    // Launch the GUI to see the results:
    std::set<std::string> args(argv, argv + argc);
    if (!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();
    return 0;
}