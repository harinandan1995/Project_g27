/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#ifndef _CS296BASE_HPP_
#define _CS296BASE_HPP_

#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>

#define	RAND_LIMIT 32767

namespace cs296
{

  //! What is the difference between a class and a struct in C++?
  class base_sim_t;
  struct settings_t;
  
  //! Why do we use a typedef
  typedef base_sim_t* sim_create_fcn(); 

  //! Simulation settings. Some can be controlled in the GUI.
  struct settings_t
  {
    // Notice the initialization of the class members in the constructor
    // How is this happening? <br>
    /*! \brief This is the default constructor for settings_t struct
     * 
     */ 
    
    settings_t() :
      view_center(0.0f, 20.0f),
      hz(60.0f),
      velocity_iterations(8),
      position_iterations(3),
      draw_shapes(1),
      draw_joints(1),
      draw_AABBs(0),
      draw_pairs(0),
      draw_contact_points(0),
      draw_contact_normals(0),
      draw_contact_forces(0),
      draw_friction_forces(0),
      draw_COMs(0),
      draw_stats(0),
      draw_profile(0),
      enable_warm_starting(1),
      enable_continuous(1),
      enable_sub_stepping(0),
      pause(0),
      single_step(0)
    {}
    
    b2Vec2 view_center;//!< Decides the center of the simulation,changing it would result in change of position of bodies in the simulation
    float32 hz;
    int32 velocity_iterations; //!< Number of times it calculates the velocity in unit time
    int32 position_iterations; //!< Number of times it calculates the position in unit time
    int32 draw_shapes; //!< Shapes that appear in the simulation
    int32 draw_joints; //!< Joints that appear in the simulation
    int32 draw_AABBs; //!< Bounding boxes appear around all shapes depending on its value
    int32 draw_pairs; //!< 
    int32 draw_contact_points; //!< Enables/Shows contact points in the simulation
    int32 draw_contact_normals; //!< Enables/Shows normal contact forces in the simulation
    int32 draw_contact_forces; //!< Enables/Shows contact forces in the simulation
    int32 draw_friction_forces; //!< Enables friction forces in the simulation
    int32 draw_COMs;//!< Centre of masses of each body appear in the simulation
    int32 draw_stats;//!< It tell about number of bodies, contacts, joints, height, balance, quality etc.
    int32 draw_profile;//!< Enables the profile view of the simulation
    int32 enable_warm_starting;//!< 
    int32 enable_continuous;//!<
    int32 enable_sub_stepping;//!<
    int32 pause; //!< Used to pause the simulation
    int32 single_step; //!< To watch the simulation step by step
  };
  
  //! Stores name of the simulation and pointer to the simulation
  struct sim_t
  {
    const char *name;//!< Name of the simulation
    sim_create_fcn *create_fcn;
    //! This is a contructor for the sim_t struct
    sim_t(const char *_name, sim_create_fcn *_create_fcn): 
      name(_name), create_fcn(_create_fcn) {;}
  };
  
  extern sim_t *sim;
  
  //! Sets the limit for number of contact points at an instance in the simulation
  const int32 k_max_contact_points = 2048;  
  
  //! Struct defined to store the contact points 
  struct contact_point_t
  {
    b2Fixture* fixtureA;//!< Properties of one of the two bodies in contact
    b2Fixture* fixtureB;//!< Properties of other body in contact with 
    b2Vec2 normal;//!< Direction of normal at point of contact
    b2Vec2 position;//!< Position of the contact point
    b2PointState state;//!< State of the contact point i.e. static(permanent point of contact) or dynamic(temporary poit of contact)
  };
  
  
  
  class base_sim_t : public b2ContactListener
  {
  public:
    //! \brief This is the default constructor for base_sim_t class <br>
     /*! Default values are declared in cs296_base.cpp
     */
    const b2World* get_world(void){return m_world;}
    
    base_sim_t();

    //! \brief Virtual destructors - amazing objects. Why are these necessary? <br>
    /*! This is a virtual destructor used to destruct m_world <br>
     * Virtual destructors are useful when you can delete an instance of a derived 
     * class through a pointer to base class <br>
     * These are used to delete the inheritances of a particular class.
     * Source : http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
     */
    virtual ~base_sim_t();
    
    void set_text_line(int32 line) { m_text_line = line; }
    void draw_title(int x, int y, const char *string);
    
    virtual void step(settings_t* settings);
	// all tthe following functions except pre_solve prevent warnings
    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); }
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); }

    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); }
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); }
	
    
    // Let derived tests know that a joint was destroyed.
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); }
    
    // Callbacks for derived classes.
    virtual void begin_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    virtual void end_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold);// used to find contact points and store them
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    }
	/*!These are protected members <br>
	 * How are protected members different from private memebers of a class in C++ ? <br>
	 * Private - only available to be accessed within the class that defines them. <br>
	 * Protected - accessible in the class that defines them and in 
	 * other classes which inherit from that class.
	 */
  protected:   
    //! This is a friend class <br>
     /*!  What are Friend classes? <br>
     * A non-member function can access the private and protected 
     * members of a class if it is declared a friend of that class. <br>
     * Source : http://www.cplusplus.com/doc/tutorial/inheritance/
     */  
    friend class contact_listener_t;
    
    b2Body* m_ground_body;//!< Pointer to ground body
    b2AABB m_world_AABB;//!< Bounding boxes around each body
    contact_point_t m_points[k_max_contact_points];
    /*!< Array of contact points with limit of 
     * k_max_contact_points contact points
     */
    int32 m_point_count;//!< Keeps the count of contact points 

    debug_draw_t m_debug_draw;//!< controls screen display and used for debugging
    int32 m_text_line;
    b2World* m_world;//!< Pointer to the world created in the simulation
	
    /*b2Body* getBall(){
		return base;
	}*/
	
    int32 m_step_count;//!<Keeps the count of steps involved in the simulation
    
    b2Profile m_max_profile;
    b2Profile m_total_profile;
  };
}

#endif
