## TODO:
- experiment with using `RTTI::SomeTrait;` and detecting those upon reflection, instead of using macros; traits can have more advanced options on how a base can propagate to derived classes, etc.
- `mInfo` in maps moves around to first map entry, so that iterations always beging with the first pair
- implement ordered maps and sets using an ordering array of indices after the `mInfo` array - that way we can directly transfer maps between ordered/unordered variations without any trouble
- use redundant map data (`mValues.mCount` and `mValues.mReserved`) for keeping track of ordering array
- map and set iterations tend to iterate to the end of mInfo, despite having gone past the inserted mCount
- when deducing this is implemented for gcc, use it to reduce a plethora of const/mutable function equivalents, and use `if consteval`
- add multiplication operators to meta types to multiply by their size
- Ditch `monocast` nonsense, and instead add Shallow semantic that affects whether verbs are executed deeply or not?
- In future standards, make sure we exclude reflected bases that don't qualify as 'direct'; route imposed bases through a semantic instead (but why??)
- Test a block that contains multiple different interleaved groups of coalesced elements for a pretty nasty bad block destruction corner case
- Partially successful block transfers that get interrupted by an exception should unallocate the items that were successfully initialized
- Why hardcode `Traits::Parent` to be not participating in hashing? Just add the trait as missing, so that it is dynamically linked depending on the context, and exclude all linking points from hashing???
- Test if vector/point/normal/sampler/etc. constructors make sense and play well with semantics, when inside containers
- Since Couple is now invoked by the user's whim, mOwners is now invalid in unit constructors. Which means that we can safely discard non Aux versions of hierarchy seek interface - just rely always on the descriptor!
- It would be _really_ cool if `Langulus::Logger` supports markdown, through `_md` literal for example? Will save on a lot of `Logger::Command` pushes
- Check where the new `Types::ForEach` pattern can be useful to reduce code
- Move ASCII image support directly to `ModAssetsImages`
- Test all containers with aggregates
- Rename Semantic to Intent, and NotSemantic to Peek or NoIntent
- Rename Crop/CropInner to Select
- Is it possible to use generator function to iterate based on concepts?? like: ForEach([](const CT::Block auto& block) {...}) ????? that would be bloody awesome

## In progress:
- remove `CT::Inner` duplicated concepts, use `Decay` when needed to use the non-inner version
- ALL CONCEPTS NEED TESTS, because i just fixed a plethora of logical mistakes in them. can's stress this enough.
- rename Any to Many, and make Any specialized for one element only?
- Separate containers into reusable components
- Many of the containers call two destructors instead of one, inherit directly from Block/BlockMap/BlockSet to avoid it

## Done:
- cleanup the concept of `CT::POD`
- Add `NameOf` corner case tests where the typename starts or ends overlapping with the provided `helper_name`
