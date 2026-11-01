## Walkthrough: Move through holders

The transfer into `holders` clears `p`, so the resource has exactly one owner, the slot. Printing `p owns nothing: yes` checks that the source is empty, and the count shows how many slots are in use.

The transfer back out clears slot 0, so the array no longer owns the resource. Reducing the count then removes the empty slot from the list of slots in use. That's the C form of `pop_back` after the element was moved out: the removed slot holds nothing, so nothing is released there.

The resource is now owned by `back` alone, and it's released once, after `End`. For the extension about copying, a copy would leave both `p` and the slot holding the block. That second owner is what the single-owner rule forbids, and a later release from both places would be a double free.
