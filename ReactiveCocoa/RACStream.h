//
//  RACStream.h
//  ReactiveCocoa
//
//  Created by Justin Spahr-Summers on 2012-10-31.
//  Copyright (c) 2012 GitHub, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RACStream;

/// A block which accepts a value from a RACStream and returns a new instance
/// of the same stream class.
///
/// Setting `stop` to `YES` will cause the bind to terminate after the returned
/// value. Returning `nil` will result in immediate termination.

// 一个接受一个从 RACStream 的值并返回相同的流类的一个新实例的块。
// 将stop值设置为Yes将导致终止后返回的值绑定。返回 'nil' 将导致立即终止。
// 权:
// 1/接收一个来自RACStream的value,并返回一个新的RACStream;
// 2/设置stop=YES将在返回value值时停止;
// 3/如果返回为nil将立即停止.
typedef RACStream *(^RACStreamBindBlock)(id value, BOOL *stop);

/// An abstract class representing any stream of values.
///
/// This class represents a monad, upon which many stream-based operations can
/// be built.
///
/// When subclassing RACStream, only the methods in the main @interface body need
/// to be overridden.

// 单词: monad:一元
// 一个抽象类，表示任何流值。
// 此类表示的单细胞，可以赖以建立许多基于工作流的操作。
// 当子类化 RACStream，只有 @interface 主体中的方法不需要重写。
// 权:
// 1/一个抽象类,表示任何流值;
// 2/这个类是一个monad, 基于operations;
// 3/子类, 不需要重写@interface主体中的方法.
@interface RACStream : NSObject

/// Returns an empty stream.

// 权: 1/返回空流.
+ (instancetype)empty;

/// Lifts `value` into the stream monad.
///
/// Returns a stream containing only the given value.

// 权:
// 1/植入一个value到一元stream中;
// 2/返回包含这个的value的stream.
+ (instancetype)return:(id)value;

/// Lazily binds a block to the values in the receiver.
///
/// This should only be used if you need to terminate the bind early, or close
/// over some state. -flattenMap: is more appropriate for all other cases.
///
/// block - A block returning a RACStreamBindBlock. This block will be invoked
///         each time the bound stream is re-evaluated. This block must not be
///         nil or return nil.
///
/// Returns a new stream which represents the combined result of all lazy
/// applications of `block`.

// 懒洋洋地将一个块绑定到接收机中的值。
// 如果您需要绑定可提前，终止或关闭一些国家只使用此设置。-flattenMap: 是更适合于所有其他情况。
// 块 - 块返回RACStreamBindBlock 。此块将被绑定的流被重新评估每一次调用。此块不能是零或返回零。
// 返回一个新的数据流代表的` block`懒惰应用的综合作用的结果。
// 权:
// 1/懒bind一个block当成values传递给receiver;
// 2/如果您需要提前终止bind，或关闭了一些state这应该只被使用. -flattenMap: 是更适合于所有其他情况.
// 3/一个RACSteamBindBlock.这个block将在每次调用时重新评估一次.这个block必须不能为nil或return nil;
// 4/返回一个block all lazy后的combined(综合)结果的新stream.
- (instancetype)bind:(RACStreamBindBlock (^)(void))block;

/// Appends the values of `stream` to the values in the receiver.
///
/// stream - A stream to concatenate. This must be an instance of the same
///          concrete class as the receiver, and should not be `nil`.
///
/// Returns a new stream representing the receiver followed by `stream`.

// 追加的` stream`的值，以在接收器中的值。
// 流 - 甲流来连接。这必须是相同的混凝土类作为接收机的一个实例，而不应是` nil` 。
// 返回表示接收随后` stream`一个新的数据流。
// 权:
// 1/appends一个values（stream）到 receiver中;
// 2/stream必须与receiver是一个相同的类,并且不能是nil;
// 3/返回一个已追加的,新的stream.
- (instancetype)concat:(RACStream *)stream;

/// Zips the values in the receiver with those of the given stream to create
/// RACTuples.
///
/// The first value of each stream will be combined, then the second value, and
/// so forth, until at least one of the streams is exhausted.
///
/// stream - The stream to zip with. This must be an instance of the same
///          concrete class as the receiver, and should not be `nil`.
///
/// Returns a new stream of RACTuples, representing the zipped values of the
/// two streams.

// 拉链与给定的流接收器创建 RACTuples 中的值。
// 每个流的第一个值将合并，然后第二个值，和如此反复，直到至少一个流用尽。
// 小河-小河与 zip。这必须作为接收器，相同的具体类的一个实例，并且不应该是 '零'。
// 返回表示两个流的压缩的值的新流 RACTuples。
// 权:
// 1/zips the values 和 给定的stream 来创建RACTuples（元组）;
// 2/ 合并stream;
// 3/合并的stream必须相同类,并且不能为nil;
// 4/返回一个新stream of RACTuples（元组）.
- (instancetype)zipWith:(RACStream *)stream;

@end

/// This extension contains functionality to support naming streams for
/// debugging.
///
/// Subclasses do not need to override the methods here.

// 权:
// 1/此扩展包含支持命名（name）流用于调试功能.
// 2/子类不需要重写这里的方法.
@interface RACStream ()

/// The name of the stream. This is for debugging/human purposes only.

// 权:
// 1/流的名称。这是仅用于调试.
@property(copy) NSString *name;

/// Sets the name of the receiver to the given format string.
///
/// This is for debugging purposes only, and won't do anything unless the
/// RAC_DEBUG_SIGNAL_NAMES environment variable is set.
///
/// Returns the receiver, for easy method chaining.

// 将接收器的名称设置为给定的格式字符串。
// 这是出于调试目的，并不做任何事，除非 RAC_DEBUG_SIGNAL_NAMES 环境变量设置。
// 返回接收机，容易方法链接。
// 权:
// 1/设置receiver的name;
// 2/出于调试目的，这里并不做任何事，除非RAC_DEBUG_SIGNAL_NAMES 环境变量设置;
// 3/返回一个receiver.（方法链 method chaining）
- (instancetype)setNameWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1, 2);

@end

/// Operations built on the RACStream primitives.
///
/// These methods do not need to be overridden, although subclasses may
/// occasionally gain better performance from doing so.

// 权:
// 1/基于 RACStream 原语操作;
// 2/这些方法不需要重写，虽然子类可能偶尔会获得更好的性能，这样做.
@interface RACStream (Operations)

/// Maps `block` across the values in the receiver and flattens the result.
///
/// Note that operators applied _after_ -flattenMap: behave differently from
/// operators _within_ -flattenMap:. See the Examples section below.
///
/// This corresponds to the `SelectMany` method in Rx.
///
/// block - A block which accepts the values in the receiver and returns a new
///         instance of the receiver's class. Returning `nil` from this block is
///         equivalent to returning an empty signal.
///
/// Examples
///
///   [signal flattenMap:^(id x) {
///       // Logs each time a returned signal completes.

// 每次返回的信号完成的日志。
///       return [[RACSignal return:x] logCompleted];
///   }];
///
///   [[signal
///       flattenMap:^(id x) {
///           return [RACSignal return:x];
///       }]
///       // Logs only once, when all of the signals complete.

// 记录只有一次，当所有的信号完成。
///       logCompleted];
///
/// Returns a new stream which represents the combined streams resulting from
/// mapping `block`.

// 在接收机中的值间映射阻止并展平的结果。
// 程序员应用 _after_ flattenMap 和 _within_ flattenMap 的行为不同,请参阅下面的示例部分。
// 这对应于在 Rx 的 'SelectMany' 方法。
// 块-块，接受接收器中的值，并返回接收器的类的一个新实例。返回此块从 ' 零' 等于返回空的信号。
// 返回一个新的流代表联合的流造成的映射阻止。
// 权:
// 1/在receiver中 map（映射）the values, 并展平result;
// 2/程序员应用 _after_ flattenMap (只调用一次)和 _within_ flattenMap (每次都调用) 的行为不同,请参阅下面的示例部分;
// 3/block返回一个新的receiver类, block=nil 将 return empty signal.
// 4/返回一个新的stream表示combined（综合）streams的result.
// 5/ This corresponds to the `SelectMany` method in Rx.
- (instancetype)flattenMap:(RACStream *(^)(id value))block;

/// Flattens a stream of streams.
///
/// This corresponds to the `Merge` method in Rx.
///
/// Returns a stream consisting of the combined streams obtained from the
/// receiver.

// 拼合流流。
// 这对应于的合并方法在 Rx
// 返回流组成的联合的溪流从接收方获得。
// 权:
// 1/Flattens a stream of streams.从receiver获得
// 5/This corresponds to the `Merge` method in Rx.
- (instancetype)flatten;

/// Maps `block` across the values in the receiver.
///
/// This corresponds to the `Select` method in Rx.
///
/// Returns a new stream with the mapped values.

// 块整个接收机中的值映射。
// 这对应于在 Rx 的 '选择' 的方法。
// 返回一个新流与映射的值。
// 权:
// 1/ This corresponds to the `Select` method in Rx.
// 2/返回一个新流与映射的值.
- (instancetype)map:(id (^)(id value))block;

/// Replaces each value in the receiver with the given object.
///
/// Returns a new stream which includes the given object once for each value in
/// the receiver.
// 权:
// 1/替换 receiver.values = object;
- (instancetype)mapReplace:(id)object;

/// Filters out values in the receiver that don't pass the given test.
///
/// This corresponds to the `Where` method in Rx.
///
/// Returns a new stream with only those values that passed.
// 权:
// 1/筛选值
// 2/This corresponds to the `Where` method in Rx.
- (instancetype)filter:(BOOL (^)(id value))block;

/// Filters out values in the receiver that equal (via -isEqual:) the provided value.
///
/// value - The value can be `nil`, in which case it ignores `nil` values.
///
/// Returns a new stream containing only the values which did not compare equal
/// to `value`.
// 权:
// 1/筛选值，等于（通过-isEqual :)所提供的value.
// 2/value可以是` nil` ，在这种情况下，它会忽略' nil`值。
- (instancetype)ignore:(id)value;

/// Unpacks each RACTuple in the receiver and maps the values to a new value.
///
/// reduceBlock - The block which reduces each RACTuple's values into one value.
///               It must take as many arguments as the number of tuple elements
///               to process. Each argument will be an object argument. The
///               return value must be an object. This argument cannot be nil.
///
/// Returns a new stream of reduced tuple values.
// 权:
// 1/解包在接收器的每个RACTuple的值映射到一个新的值。
// 2/从而简化每个RACTuple的value转换成一个value block。它必须采取许多argument作为tuple的elements数目来处理。每个argument将是一个object元素。返回值必须是一个object。这种argument不能是nil。
// 3/返回简化tuple值的一个新的stream。
- (instancetype)reduceEach:(id (^)())reduceBlock;

/// Returns a stream consisting of `value`, followed by the values in the
/// receiver.
// 返回流组成的` value` ，receive后面的values。
- (instancetype)startWith:(id)value;

/// Skips the first `skipCount` values in the receiver.
///
/// Returns the receiver after skipping the first `skipCount` values. If
/// `skipCount` is greater than the number of values in the stream, an empty
/// stream is returned.
// 权:
// 1/跳过`skipCount` values
// 2/跳过第一个` skipCount`values后返回receiver。
// 3/如果` skipCount`大于stream中的值的数目，则返回一个empty。
- (instancetype)skip:(NSUInteger)skipCount;

/// Returns a stream of the first `count` values in the receiver. If `count` is
/// greater than or equal to the number of values in the stream, a stream
/// equivalent to the receiver is returned.
// 权:
// 1/返回在receiver中的第一个`count`value。
// 2/如果` count`大于或等于stream中的值的数目，则返回相当于receiver的steam。
- (instancetype)take:(NSUInteger)count;

/// Zips the values in the given streams to create RACTuples.
///
/// The first value of each stream will be combined, then the second value, and
/// so forth, until at least one of the streams is exhausted.
///
/// streams - The streams to combine. These must all be instances of the same
///           concrete class implementing the protocol. If this collection is
///           empty, the returned stream will be empty.
///
/// Returns a new stream containing RACTuples of the zipped values from the
/// streams.
// 权:
// 1/这些都必须是同一个具体class实现该protocol的实例。如果该collection为空，则返回的stream将是empty的。
+ (instancetype)zip:(id <NSFastEnumeration>)streams;

/// Zips streams using +zip:, then reduces the resulting tuples into a single
/// value using -reduceEach:
///
/// streams     - The streams to combine. These must all be instances of the
///               same concrete class implementing the protocol. If this
///               collection is empty, the returned stream will be empty.
/// reduceBlock - The block which reduces the values from all the streams
///               into one value. It must take as many arguments as the
///               number of streams given. Each argument will be an object
///               argument. The return value must be an object. This argument
///               must not be nil.
///
/// Example:
///
///   [RACStream zip:@[ stringSignal, intSignal ] reduce:^(NSString *string, NSNumber *number) {
///       return [NSString stringWithFormat:@"%@: %@", string, number];
///   }];
///
/// Returns a new stream containing the results from each invocation of
/// `reduceBlock`.
// 权:
// 1/这些都必须是同一个具体class实现该protocol的实例。如果该collection为空，则返回的stream将是empty的。
// 2/reduceBlock - 从所有stream reduce(简化)的values到一个values的block。它必须采取许多argument作为给定的stream的数目。每个argument将是一个object argument。返回值必须是一个object。这种argument不能是nil。
+ (instancetype)zip:(id <NSFastEnumeration>)streams reduce:(id (^)())reduceBlock;

/// Returns a stream obtained by concatenating `streams` in order.
// 权:
// 1/concatenating 串联
+ (instancetype)concat:(id <NSFastEnumeration>)streams;

/// Combines values in the receiver from left to right using the given block.
///
/// The algorithm proceeds as follows:
///
///  1. `startingValue` is passed into the block as the `running` value, and the
///  first element of the receiver is passed into the block as the `next` value.
///  2. The result of the invocation is added to the returned stream.
///  3. The result of the invocation (`running`) and the next element of the
///  receiver (`next`) is passed into `block`.
///  4. Steps 2 and 3 are repeated until all values have been processed.
///
/// startingValue - The value to be combined with the first element of the
///                 receiver. This value may be `nil`.
/// reduceBlock   - The block that describes how to combine values of the
///                 receiver. If the receiver is empty, this block will never be
///                 invoked. Cannot be nil.
///
/// Examples
///
///      RACSequence *numbers = @[ @1, @2, @3, @4 ].rac_sequence;
///
///      // Contains 1, 3, 6, 10
///      RACSequence *sums = [numbers scanWithStart:@0 reduce:^(NSNumber *sum, NSNumber *next) {
///          return @(sum.integerValue + next.integerValue);
///      }];
///
/// Returns a new stream that consists of each application of `reduceBlock`. If the
/// receiver is empty, an empty stream is returned.
- (instancetype)scanWithStart:(id)startingValue reduce:(id (^)(id running, id next))reduceBlock;

/// Combines values in the receiver from left to right using the given block
/// which also takes zero-based index of the values.
///
/// startingValue - The value to be combined with the first element of the
///                 receiver. This value may be `nil`.
/// reduceBlock   - The block that describes how to combine values of the
///                 receiver. This block takes zero-based index value as the last
///                 parameter. If the receiver is empty, this block will never
///                 be invoked. Cannot be nil.
///
/// Returns a new stream that consists of each application of `reduceBlock`. If the
/// receiver is empty, an empty stream is returned.
- (instancetype)scanWithStart:(id)startingValue reduceWithIndex:(id (^)(id running, id next, NSUInteger index))reduceBlock;

/// Combines each previous and current value into one object.
///
/// This method is similar to -scanWithStart:reduce:, but only ever operates on
/// the previous and current values (instead of the whole stream), and does not
/// pass the return value of `reduceBlock` into the next invocation of it.
///
/// start       - The value passed into `reduceBlock` as `previous` for the
///               first value.
/// reduceBlock - The block that combines the previous value and the current
///               value to create the reduced value. Cannot be nil.
///
/// Examples
///
///      RACSequence *numbers = @[ @1, @2, @3, @4 ].rac_sequence;
///
///      // Contains 1, 3, 5, 7
///      RACSequence *sums = [numbers combinePreviousWithStart:@0 reduce:^(NSNumber *previous, NSNumber *next) {
///          return @(previous.integerValue + next.integerValue);
///      }];
///
/// Returns a new stream consisting of the return values from each application of
/// `reduceBlock`.
- (instancetype)combinePreviousWithStart:(id)start reduce:(id (^)(id previous, id current))reduceBlock;

/// Takes values until the given block returns `YES`.
///
/// Returns a stream of the initial values in the receiver that fail `predicate`.
/// If `predicate` never returns `YES`, a stream equivalent to the receiver is
/// returned.
- (instancetype)takeUntilBlock:(BOOL (^)(id x))predicate;

/// Takes values until the given block returns `NO`.
///
/// Returns a stream of the initial values in the receiver that pass `predicate`.
/// If `predicate` never returns `NO`, a stream equivalent to the receiver is
/// returned.
- (instancetype)takeWhileBlock:(BOOL (^)(id x))predicate;

/// Skips values until the given block returns `YES`.
///
/// Returns a stream containing the values of the receiver that follow any
/// initial values failing `predicate`. If `predicate` never returns `YES`,
/// an empty stream is returned.
- (instancetype)skipUntilBlock:(BOOL (^)(id x))predicate;

/// Skips values until the given block returns `NO`.
///
/// Returns a stream containing the values of the receiver that follow any
/// initial values passing `predicate`. If `predicate` never returns `NO`, an
/// empty stream is returned.
- (instancetype)skipWhileBlock:(BOOL (^)(id x))predicate;

/// Returns a stream of values for which -isEqual: returns NO when compared to the
/// previous value.
- (instancetype)distinctUntilChanged;

@end

@interface RACStream (Deprecated)

- (instancetype)sequenceMany:(RACStream *(^)(void))block __attribute__((deprecated("Use -flattenMap: instead")));

- (instancetype)scanWithStart:(id)startingValue combine:(id (^)(id running, id next))block __attribute__((deprecated("Renamed to -scanWithStart:reduce:")));

- (instancetype)mapPreviousWithStart:(id)start reduce:(id (^)(id previous, id current))combineBlock __attribute__((deprecated("Renamed to -combinePreviousWithStart:reduce:")));

@end
