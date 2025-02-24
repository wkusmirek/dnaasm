/**
 * \file existreturnpath.hpp
 * \brief the C++ file with implementation of function for checking if exist return path for edge
 */

#ifndef EXIST_RETURN_PATH_HPP
#define EXIST_RETURN_PATH_HPP

#include <boost/bind.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>

namespace dnaasm { namespace dbj {

    template < typename Graph>
    /**
     * \brief Helping class to check if exist return path for definite edge.
     */
    class BackPathVisitor : public boost::dfs_visitor<> {
        typedef typename boost::graph_traits < Graph >::vertex_descriptor Vertex; //unsigned long for vecS
    public:
        BackPathVisitor(const Vertex& toFind, bool& found): toFind_(toFind), found_(found) {}

        template <class V, class G>
        void start_vertex(V v, const G&) {}

        template < typename V, typename G >
        void discover_vertex(V u, const G & g) {
            if (u == toFind_) {
                found_ = true;
            }
        }

        bool getFound() const { return found_; }
    private:
        const Vertex toFind_;
        bool& found_;
    };

    /**
     * \brief Checks if exist the path target -> source for given edge.
     *
     * \param g reference to actual Graph object
     * \param e edge descriptor for which function will check return path existing
     * \return returns true if exist the path target -> source for given edge or false if not exist.
     */
    template<typename Graph>
    bool existReturnPath(const Graph& g, const typename boost::graph_traits<Graph>::edge_descriptor& e) {

        typedef typename boost::graph_traits < Graph >::vertex_descriptor Vertex; //unsigned long for vecS
        Vertex s = source(e, g);
        Vertex t = target(e, g);
        if (s == t)//for self-loop edges - always true
            return true;

        std::vector<boost::default_color_type> c(boost::num_vertices(g), boost::white_color);
        bool found = false;
        BackPathVisitor<Graph> vis(s, found);
        depth_first_visit(g, t, vis,
                          boost::make_iterator_property_map(c.begin(), get(boost::vertex_index, g), c[0]),
                          boost::bind(&BackPathVisitor<Graph>::getFound, &vis)
                         );
        return found;
    }

}}

#endif    //EXIST_RETURN_PATH_HPP
