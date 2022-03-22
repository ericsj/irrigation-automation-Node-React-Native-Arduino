import { StyledTextContainer } from "./styles";

const TextContainer = (props) => {
    return <StyledTextContainer {...props}>{props.children}</StyledTextContainer>
}

export default TextContainer