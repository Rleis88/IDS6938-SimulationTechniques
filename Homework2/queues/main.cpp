/*
  A simple program that simulates 5 MM1 queues at an airport. The first queue
  feeds 3 other queues that work in parallel. These feed a final queue.
  Simulation runs until error below threshold and, at the end,
  a performance evaluation report is shown, and logs are generated
  for plotting and analysis.
*/

using namespace std;

#include <random>
#include "customer.h"
#include "mm1_queue.h"


std::random_device rd;

void pause()
{
 std::string sInputString;
 // Wait for input from stdin (the keyboard)
 cout << "Continue (y)?";
 std::cin >> sInputString;
}

// Got information from Piazza but went through with study group

int main(int argc, char* argv[])
{
   int next = 0;
//   test_random_number_generator();

   for (int cur_lambda = 3; cur_lambda < 34; cur_lambda++)
   {
      
	   //TODO Create MM1_Queue objects to capture the airport senario.

	   //************************************************************
	   MM1_Queue Checkin;
	   Checkin.set_file_names("Checkin_log.txt", "Checkin_wait.txt", "Checkin_service.txt");
	   Checkin.set_lambda(6); // for this assignment this is set to a variable from the for loop.
	   Checkin.set_mu(53);
	   Checkin.initialize();
	   Checkin.set_seed(rd(), rd()); 

	   MM1_Queue Securityone;
	   Securityone.set_file_names("Securityone_log.txt", "Securityone_wait.txt", "Securityone_service.txt");
	   Securityone.set_lambda(6); // for this assignment this is set to a variable from the for loop.
	   Securityone.set_mu(20);
	   Securityone.autogenerate_new_arrivals(false);
	   Securityone.initialize();
	   Securityone.set_seed(rd(), rd()); 
	   
	   MM1_Queue Securitytwo;
	   Securitytwo.set_file_names("Securitytwo_log.txt", "Securitytwo_wait.txt", "Securitytwo_service.txt");
	   Securitytwo.set_lambda(6); // for this assignment this is set to a variable from the for loop.
	   Securitytwo.set_mu(20);
	   Securitytwo.autogenerate_new_arrivals(false);
	   Securitytwo.initialize();
	   Securitytwo.set_seed(rd(), rd()); 

	   MM1_Queue Securitythree;
	   Securitythree.set_file_names("Securitythree_log.txt", "Securitythree_wait.txt", "Securitythree_service.txt");
	   Securitythree.set_lambda(6); // for this assignment this is set to a variable from the for loop.
	   Securitythree.set_mu(20);
	   Securitythree.autogenerate_new_arrivals(false);
	   Securitythree.initialize();
	   Securitythree.set_seed(rd(), rd()); 

	   MM1_Queue Departure;
	   Departure.set_file_names("Departure_log.txt", "Departure_wait.txt", "Departure_service.txt");
	   Departure.set_lambda(6); // for this assignment this is set to a variable from the for loop.
	   Departure.set_mu(80);
	   Departure.initialize();
	   Departure.set_seed(rd(), rd()); 
   for (; 
		//TODO: add is_within_error_range check
	   !Checkin.is_within_error_range(0.002) ||
	   !Securityone.is_within_error_range(0.002) ||
	   !Securitytwo.is_within_error_range(0.002) ||
	   !Securitythree.is_within_error_range(0.002)
       ;)
   {
	   Customer cust  = Checkin.process_next_event();   // =  TODO: process next event;
	   Customer cust2 = Securityone.process_next_event();  // =  TODO: process next event;
	   Customer cust3 = Securitytwo.process_next_event();  // =  TODO: process next event;
	   Customer cust4 = Securitythree.process_next_event();  // =  TODO: process next event;
	   Customer cust5 = Departure.process_next_event();  // =  TODO: process next event; //TODO: one more process_next_event for the last object.

       if (cust.get_type() == Customer::COMPLETED())
       {
          switch(next)
          {
            case 0:
				//TODO add_external_arrival() for your security gates;
				Securityone.add_external_arrival();
                 break;
            case 1:
				//TODO add_external_arrival() for your security gates;
				Securitytwo.add_external_arrival();
                 break;
            case 2:
                //TODO add_external_arrival() for your security gates;
				Securitythree.add_external_arrival();
                 break;
          }
          next++;
          if (next%3==0) next = 0;
       }
       if (cust2.get_type() == Customer::COMPLETED() || cust3.get_type() == Customer::COMPLETED() || cust4.get_type() == Customer::COMPLETED())
       {
		   //TODO add_external_arrival(); on your final boarding MM1_Queue object
		   Departure.add_external_arrival();
       }
   }



   //TODO Output statistics airport senario.
	Checkin.get_current_time();
	Checkin.plot_results_output();
	Securityone.get_current_time();
	Securityone.plot_results_output();
	Securitytwo.get_current_time();
	Securitytwo.plot_results_output();
	Securitythree.get_current_time();
	Securitythree.plot_results_output();
	Departure.get_current_time();
	Departure.plot_results_output();

	Checkin.output(); cout << endl << endl;
	Securityone.output(); cout << endl << endl;
	Securitytwo.output(); cout << endl << endl;
	Securitythree.output(); cout << endl << endl;
	Departure.output(); cout << endl << endl;

   //**************************************************************************



   }

   return(0);
}

