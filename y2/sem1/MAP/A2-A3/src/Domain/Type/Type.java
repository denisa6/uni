package Domain.Type;
import Domain.Value.Value;

public interface Type {
    Value getDefaultValue();
    Type deepCopy();
}
