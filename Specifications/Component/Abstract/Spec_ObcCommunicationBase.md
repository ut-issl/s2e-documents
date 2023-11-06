# Specification of UartCommunicationWithObc class

## 1.  Overview
1. Functions
   - The `UartCommunicationWithObc` class is an abstract class to communicate with `OnBoardComputer`.
   - Component classes can use this abstract class to emulate telemetry/command communication with an `OnBoardComputer`.
   - This class also supports communication with `C2A` in the `ObcWithC2a` class.
2. Related files
   - on_board_computer.cpp, hpp
   - example_serial_communication_with_obc.cpp, hpp
     - Users can find an example of using this class.
3. How to use
   - Inherit this class by component class.
     - Users need to set `sils_port_id` and target `OnBoardComputer` for the communication.
   - This class has the following protected functions for telemetry/command communication. Users can call these functions in the `MainRoutine` of the component.
     ```cpp
     int ReceiveCommand(const int offset, const int rec_size);
     int SendTelemetry(const int offset); 
     ```
   - In the protected functions, the following pure virtual functions are called. Users need to define the functions in the subclass.
     ```cpp
     virtual int ParseCommand(const int cmd_size)=0;
     virtual int GenerateTelemetry()=0;
     ```

## 2. Explanation of Algorithm
1. Constructors
   1. overview
      - In the constructors, the communication port for the `OnBoardComputer` is connected.
      - If another component already connects the port, the connection function returns an error, and the constructors output a message.
   2. inputs and outputs
      - Both constructors require `sils_port_id` and target `OnBoardComputer`.
      - Users can set the communication data buffer size. When users do not put the size, the value is automatically set as the maximum value.
        - The maximum value is 1024, and it is defined in `uart_port.hpp`  
   3. algorithm
      - N/A
   4. note
      - N/A
2. Destructor
   1. overview
      - In the destructor, the communication port is closed.
      - If another component has closed the port, the close function returns an error, and the constructors output a message.
   2. inputs and outputs
      - N/A
   3. algorithm
      - N/A 
   4. note
      - N/A
3. ReceiveCommand
   1. overview
      - Receive command data sent from the OBC.
   2. inputs and outputs
      - input
        - offset: offset value of the rx_buffer [Byte]
        - rec_size: receiving data size = length of the command [Byte]
      - output
        - return: Error code. (<=0: Error was happened)
   3. algorithm
      - N/A 
   4. note
      - N/A
4. SendTelemetry
   1. overview
      - Send telemetry data to the OBC.
   2. inputs and outputs
      - input
        - offset: offset value of the tx_buffer [Byte]
      - output
        - return: Error code. 0: fine, <0: Error.
   3. algorithm
      - N/A 
   4. note
      - N/A
5. ParseCommand
   1. overview
      - Users need to define this function to analyze the command.
   2. inputs and outputs
      - input
        - cmd_size: command side [Byte]
      - output
        - return: Error code. (<=0: Error was happened)
   3. algorithm
      - N/A 
   4. note
      - N/A
6. GenerateTelemetry
   1. overview
      - Users need to define this function to make telemetry.
  2. inputs and outputs
      - input: N/A
      - output
        - return: send data size [Byte]
   3. algorithm
      - N/A 
   4. note
      - N/A
## 3. Results of verifications
- N/A

## 4. References
- N/A
