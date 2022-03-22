import { StyledText } from "./styles";

const CustomText = (props) => {
    return <StyledText {...props}>{props.children}</StyledText>
}

export default CustomText