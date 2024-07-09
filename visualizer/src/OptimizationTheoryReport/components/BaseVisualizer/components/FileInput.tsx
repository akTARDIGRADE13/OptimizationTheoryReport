import React, { useState } from 'react';
import styles from './FileInput.module.css';

interface FileInputProps {
  onFileChange: (files: string | null) => void;
}

const FileInput: React.FC<FileInputProps> = ({ onFileChange }) => {
  const [fileName, setFileName] = useState<string | null>(null);
  const handleFileChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    const files = event.target.files;
    const reader = new FileReader();
    reader.onload = (e) => {
      onFileChange(e.target?.result as string);
    };
    setFileName(files?.[0]?.name || null);
    if (files?.[0]) {
      reader.readAsText(files[0]);
    }
  };

  return (
    <form>
      <input
        type="file"
        name="file"
        id="file"
        className={styles['file-input']}
        multiple
        onChange={handleFileChange}
      />
      <label htmlFor="file" className={styles['file-label']}>
        {fileName ? fileName : '入力ファイルを選択'}
      </label>
    </form>
  );
};

export default FileInput;
