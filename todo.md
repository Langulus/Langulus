## TODO:
- `mInfo` in maps moves around to first map entry, so that iterations always beging with the first pair
- Implement ordered maps and sets using an ordering array of indices after the `mInfo` array - that way we can directly transfer maps between ordered/unordered variations without any trouble
- Use redundant map data (`mValues.mCount` and `mValues.mReserved`) for keeping track of ordering array
- Map and set iterations tend to iterate to the end of mInfo, despite having gone past the inserted mCount
- When deducing this is implemented for gcc, use it to reduce a plethora of const/mutable function equivalents, and use `if consteval`
- Add multiplication operators to meta types to multiply by their size
- In future standards, make sure we exclude reflected bases that don't qualify as 'direct'; route imposed bases through a semantic instead (but why??)
- Test a block that contains multiple different interleaved groups of coalesced elements for a pretty nasty bad block destruction corner case
- Partially successful block transfers that get interrupted by an exception should unallocate the items that were successfully initialized
- Why hardcode `Traits::Parent` to be not participating in hashing? Just add the trait as missing, so that it is dynamically linked depending on the context, and exclude all linking points from hashing???
- Test if vector/point/normal/sampler/etc. constructors make sense and play well with semantics, when inside containers
- Since `Couple` is now invoked by the user's whim, `mOwners` is now invalid in unit constructors. Which means that we can safely discard non Aux versions of hierarchy seek interface - just rely always on the descriptor!
- It would be _really_ cool if `Langulus::Logger` supports markdown, through `_md` literal for example? Will save on a lot of `Logger::Command` pushes
- Check where the new `Types::ForEach` pattern can be useful to reduce code
- Move ASCII image support directly to `ModAssetsImages`
- Is it possible to use generator function to iterate blocks based on concepts?? like: `ForEach([](const CT::Block auto& block) {...})` ????? that would be bloody awesome
- Test all containers with `void*/const void*`
- Test all containers with double pointers, including for `void**/const void* const*`
- Test containers with function pointers, make them executable
- `Many::Past()` and `Many::Future()` should accept arguments as filters? or even better: remove missing states, add new containers instead! use the ones in Flow
- Improve color multiplication, currently oversaturates, must be renormalized after multiplication
- Events wouldn't be serializable or deterministic with this kinds of timestamp. Use the relative time context for it?
- RTTI origin type reflector doubles the compilation time - minimize those. Luckily disabling `NameOf` didn't affect anything - just the main reflection routine does.
- Unnecessary Block code includes double the compilation time - minimize those. Maybe separate include files with separate intents?
- Separate `CT` into a separate concept library, carry all canonical types like `A::Block` and `A::Verb` with it?
- Extensive `Block::SmartPush` tests are needed - preserving states, like staticness, must be ensured.
- `Derive`/`Integrate` verb
- Constants tested in `RTTITest`
- Remove `CustomNameOf` wrappers when constexpr variables can be moved outside scopes in newer standards
- `Traits::Time` conflicts undetectedly with `Langulus::Time` - fix it!
- Separate containers into reusable components
- Make `Any` specialized for one element only (std::any analogy)?
- `TestTemporal.cpp` moved to Entity library - make it work, and it is going to be a big deal!
- Block::Emplace doesn't return a handle if sparse!
- Open/Closed range support in Code parser
- Handle escapes in Code's string/char parser

## In progress:
- ALL CONCEPTS NEED TESTS, because I just fixed a plethora of logical mistakes in them. can't stress this enough.
- Test all containers with aggregates
- Ditch `monocast` nonsense, and instead add `Shallow` intent that affects whether verbs are executed deeply or not?
- Code should use `{}` instead of `[]` for nested code blocks

## Done:
- Cleaned up the concept of `CT::POD`
- Added `NameOf` corner case tests where the typename starts or ends overlapping with the provided `helper_name`
- `Many` of the containers call two destructors instead of one, inherit directly from `Block/BlockMap/BlockSet` to avoid it
- Rename `Crop/CropInner` to `Select`
- Fix vector swizzling with itself, once and for all
- Fix tags assigning different tags
- Fix scaling/translation sneaking in normal transformation in ASCII rasterizer
- Renamed `Any` to `Many`
- Removed `CT::Inner` duplicated concepts, use `Decay` when needed to use the non-inner version.
- Instead of appending a `Logger::Tabs{}`, just make a variant of `Logger::<Type>Tab`!
- Rename `Semantic` to `Intent`, and `NotSemantic` to `NoIntent`
- Standalone constants reflection

## Abandoned:
- Experiment with using `RTTI::SomeTrait;` and detecting those upon reflection, instead of using macros; traits can have more advanced options on how a base can propagate to derived classes, etc.
