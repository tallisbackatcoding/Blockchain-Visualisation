# Blockchain

This Blockchain have functionalities such as: 
- add a identifier to the blockchain node
- remove nodes from the blockchain with a nid identifier
- add a identifier block to nodes identified
- remove the identified blocks from all nodes where these blocks are present
- list all nodes by their identifiers
- synchronize all of the nodes with each other

Data Structures such as Sequential Set, Binary Tree Set and String Array were implemented from scratch.

More info is provided below:

```add node nid``` add a nid identifier to the blockchain node.<br /> 
```rm node nid...``` remove nodes from the blockchain with a nid identifier. If nid is '*', then all nodes are impacted.<br /> 
```add block bid nid...``` add a bid identifier block to nodes identified by nid. If nid is '*', then all nodes are impacted.<br /> 
```rm block bid...``` remove the bid identified blocks from all nodes where these blocks are present.<br /> 
```ls``` list all nodes by their identifiers. The option -l attaches the blocks bid's associated with each node.<br /> 
```sync``` synchronize all of the nodes with each other. Upon issuing this command, all of the nodes are composed of the same blocks.<br /> 
```quit``` save and leave the blockchain.
The blockchain prompt must display (see example below):

a [ character<br /> 
a first letter that indicates the state of synchronization of the chain:<br /> 
```"s"``` if the blockchain is synchronized<br /> 
```"-"``` if the blockchain is not synchronized.<br /> 
```n``` number of nodes in the chain.<br /> 
the "]> " string (with a space<br /> 
