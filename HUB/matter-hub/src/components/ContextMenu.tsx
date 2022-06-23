import React from "react"
import ReactDOM, { createPortal } from "react-dom";

export interface ContextMenuProps {
    children: React.ReactNode | React.ReactNode[];
    open: boolean;
    setOpen: React.Dispatch<React.SetStateAction<boolean>>;
    rootNode: string;
}

export default function ContextMenu(props: ContextMenuProps) {
    const menuRef = React.useRef<HTMLDivElement>(null);

    React.useEffect(() => {
        function handleClickOutside(event: MouseEvent) {
            const target = event.target as Node;
            const domNode = ReactDOM.findDOMNode(menuRef.current);

            if (!domNode?.contains(target)) {
                props.setOpen(false);
            }
        }

        document.addEventListener("mousedown", handleClickOutside);

        return (() => {
            document.removeEventListener("mousedown", handleClickOutside);
        });
    }, [menuRef, props])

    return props.open ?  (
        <>
            {createPortal(
                <div className="context-menu" ref={menuRef}>
                    {props.children}
                </div>,
                document.querySelector(props.rootNode)!
            )}
        </>
    ) : null;
}