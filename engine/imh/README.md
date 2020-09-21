# In-Memory (Heap) engine

This engine stores records in volatile memory, which means the data is permanently erased upon termination of the program.
Only use this engine for temporary work areas or for non-critical and temporary data (session management, caching)

Currently, the engine does not use byte packing due to performance costs.
This feature might be added in the future though.
Pull requests for implementing this function will be highly appreciated.