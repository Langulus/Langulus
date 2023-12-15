fix anyness tests with hopefully consistent hashes
make sure all bases are reflected for external types immediately on module load, probably revert the use of type retrievers?
remove old std::hash specialization, as these are now seemlessly integrated in HashOf?
cleanup the concept of CT::POD
experiment with using RTTI::SomeTrait; and detecting those upon reflection, instead of using macros; traits can have more advanced options on how a base can propagate to derived classes, etc.